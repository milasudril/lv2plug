//@	{"targets":[{"name":"test","type":"application"}]}

#include "test.hpp"
#include <vector>
#include <cassert>

int main()
	{
	std::vector<float> buffer_a(64);
	std::vector<float> buffer_b(64);
	MonophonicSynth::PortMap ports;
	ports.connect(MonophonicSynth::Ports::CUTOFF,buffer_a.data());
	ports.connect(MonophonicSynth::Ports::AUDIO_OUT,buffer_b.data());

	assert(buffer_a.data()==ports.get<MonophonicSynth::Ports::CUTOFF>());
	assert(buffer_b.data()==ports.get<MonophonicSynth::Ports::AUDIO_OUT>());
	return 0;
	}
