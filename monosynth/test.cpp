//@	{
//@	"targets":
//@		[{"name":"monosynth.so","type":"lib_dynamic","dependencies":
//@			[{"ref":"lv2plug","rel":"external"}]
//@		}]
//@	}

#include "test.hpp"
#include <lv2plug/lv2plug.hpp>

namespace
{
class DspEngine:public LV2Plug::Plugin<MonophonicSynth::PluginDescriptor>
	{
	public:
		DspEngine(double fs,const char* path_bundle,const LV2Plug::FeatureDescriptor& features);

		void activate()
			{}

		void deactivate()
			{}

		void process(size_t n_frames) noexcept;

	private:
		double m_fs;
		LV2Plug::FeatureDescriptor m_features;
	};

DspEngine::DspEngine(double fs,const char* path_bundle,const LV2Plug::FeatureDescriptor& features):
	m_fs(fs),m_features(features)
	{}

void DspEngine::process(size_t n_frames) noexcept
	{}
}

const LV2_Descriptor& LV2Plug::main()
	{
	return LV2Plug::descriptorGet<DspEngine>();
	}
