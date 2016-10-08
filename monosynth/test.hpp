// This file has been generated by ../lv2spectohpp.php
#ifndef MONOPHONICSYNTH_TEST_HPP
#define MONOPHONICSYNTH_TEST_HPP
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>

namespace MonophonicSynth
	{
	struct PluginDescriptor
		{
		static constexpr const char* NAME="Monophonic synth";
		static constexpr const char* nameGet() noexcept
			{return NAME;}

		static constexpr const char* URI="http://example.org/monosynth";
		static constexpr const char* uriGet() noexcept
			{return URI;}

		static constexpr const char* BINARY="monosynth.so";
		static constexpr const char* binaryGet() noexcept
			{return BINARY;}

		static constexpr const char* MAINTAINER="Torbjörn Rathsman";
		static constexpr const char* maintainerGet() noexcept
			{return MAINTAINER;}

		static constexpr const char* LICENSE="https://opensource.org/licenses/isc";
		static constexpr const char* licenseGet() noexcept
			{return LICENSE;}

		static constexpr const char* TYPE="InstrumentPlugin";
		static constexpr const char* typeGet() noexcept
			{return TYPE;}


		struct Ports
			{
			static constexpr unsigned int MIDI_IN=0;
			static constexpr unsigned int CUTOFF=1;
			static constexpr unsigned int AUDIO_OUT=2;

			static constexpr unsigned int PORT_COUNT=3;

			template<unsigned int port_id>
			struct TypeGet
				{typedef void type;};

			static constexpr const char* PORTNAMES[]={"MIDI in","Cutoff","Audio out",nullptr};
			};
		};

	template<>
	struct PluginDescriptor::Ports::TypeGet<PluginDescriptor::Ports::MIDI_IN>
			{typedef const LV2_Atom_Sequence* type;};

	template<>
	struct PluginDescriptor::Ports::TypeGet<PluginDescriptor::Ports::CUTOFF>
			{typedef const float* type;};

	template<>
	struct PluginDescriptor::Ports::TypeGet<PluginDescriptor::Ports::AUDIO_OUT>
			{typedef float* type;};

	}
#endif
