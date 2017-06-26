//@	{"targets":[{"name":"targetlv2spechook.o","type":"object"}]}

#include "targetlv2spechook.hpp"

using namespace Maike;

TargetLV2SpecHook::TargetLV2SpecHook(const ParameterSetDumpable& params):
	m_intpret(params),m_loader(m_intpret)
	{
	}

TargetLV2SpecHook* TargetLV2SpecHook::create(const ParameterSetDumpable& params)
	{return new TargetLV2SpecHook(params);}

void TargetLV2SpecHook::destroy() noexcept
	{delete this;}

void TargetLV2SpecHook::configClear()
	{
	m_intpret.configClear();
	}


TargetLV2SpecHook& TargetLV2SpecHook::configAppendDefault()
	{
	m_intpret.configAppendDefault();
	return *this;
	}

TargetLV2SpecHook& TargetLV2SpecHook::configAppend(const ResourceObject& lv2specoptions)
	{
	m_intpret.configAppend(lv2specoptions);
	return *this;
	}

void TargetLV2SpecHook::configDump(ResourceObject& lv2specoptions) const
	{
	m_intpret.configDump(lv2specoptions);
	}
