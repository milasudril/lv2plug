//@	{
//@	"targets":
//@		[{"name":"monosynth.so","type":"lib_dynamic","dependencies":
//@			[{"ref":"lv2plug","rel":"external"}]
//@		}]
//@	}

#include "test.hpp"
#include <lv2plug/lv2plug.hpp>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <cmath>

class PRIVATE DspEngine:public LV2Plug::Plugin<MonophonicSynth::PluginDescriptor>
	{
	public:
		DspEngine(double fs,const char* path_bundle,const LV2Plug::FeatureDescriptor& features);

		void process(size_t n_frames) noexcept;

	private:
		double m_fs;
		LV2Plug::FeatureDescriptor m_features;
		int m_key;
		float m_amplitude;
		float m_phi;
		float m_v_prev;

		void generate(size_t N);
		void eventsGet();
	};

DspEngine::DspEngine(double fs,const char* path_bundle,const LV2Plug::FeatureDescriptor& features):
	m_fs(fs),m_features(features),m_key(69),m_amplitude(0.0f),m_phi(0.0f),m_v_prev(0.0f)
	{}

static float frequencyGet(int key)
	{return 440.0f*exp2( (key - 69.0f)/12.0f );}

static float constexpr pi()
	{return std::acos(-1.0f);}

template<class T,size_t N>
struct Array
	{
	T data[N];
	static constexpr size_t size() noexcept
		{return N;}
	};

template<size_t N>
static constexpr Array<float,N> make_ramp()
	{
	Array<float,N> ret{};
	for(size_t k=0;k<N;++k)
		{
		auto r=static_cast<float>(k)/N;
		ret.data[k]=-1.0f*(1.0f - r) + r;
		}
	return ret;
	}

constexpr auto ramp=make_ramp<1024>();

void DspEngine::generate(size_t n_frames)
	{
	auto buffer=portmap().get<Ports::AUDIO_OUT>();
	auto fc=*portmap().get<Ports::CUTOFF>();

	auto f=frequencyGet(m_key)/m_fs;
	auto a=m_amplitude;

	auto phi=m_phi;
	auto v_prev=m_v_prev;
	while(n_frames!=0)
		{
		auto i=static_cast<size_t>(phi);
		auto v=fc*a*ramp.data[i] + (1.0f - fc)*v_prev;
		*buffer=v;
		v_prev=v;

		++buffer;
		phi+=ramp.size()*f;
		if(phi >= ramp.size() )
			{ phi-=ramp.size(); }
		--n_frames;
		}
	m_v_prev=v_prev;
	m_phi=phi;
	}

void DspEngine::eventsGet()
	{
	auto midi_in=portmap().get<Ports::MIDI_IN>();
	if(midi_in==nullptr)
		{return;}
	LV2_Atom_Event* ev = lv2_atom_sequence_begin(&(midi_in->body));
	while(!lv2_atom_sequence_is_end(&(midi_in->body)
		,midi_in->atom.size,ev))
		{
		if(ev->body.type==m_features.midi())
			{
			const uint8_t* const msg=(const uint8_t*)(ev + 1);
			switch(lv2_midi_message_type(msg))
				{
				case LV2_MIDI_MSG_NOTE_ON:
					m_key=msg[1];
					m_amplitude=msg[2]/127.0f;
					printf("%p\n",portmap().get<Ports::CUTOFF>());
					break;

				case LV2_MIDI_MSG_NOTE_OFF:
					if(m_key==msg[1])
						{m_amplitude=0.0f;}
					break;

				default:
					break;
				}
			}
		ev = lv2_atom_sequence_next(ev);
		}
	}

void DspEngine::process(size_t n_frames) noexcept
	{
	eventsGet();
	generate(n_frames);
	}

const LV2_Descriptor& LV2Plug::main()
	{
	return LV2Plug::descriptorGet<DspEngine>();
	}
