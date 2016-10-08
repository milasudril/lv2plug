//@	{
//@	 "targets":[{"name":"targetlv2spechook.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2spechook.o","rel":"implementation"}]
//@	}

#ifndef MAIKE_TARGETLV2SPECHOOK_HPP
#define MAIKE_TARGETLV2SPECHOOK_HPP

#include <maike/target_hook.hpp>

#include "targetlv2speccompiler.hpp"
#include "targetlv2specloader.hpp"
#include "targetlv2specfactory.hpp"

namespace Maike
	{
	class PRIVATE TargetLV2SpecHook final:public Target_Hook
		{
		public:
			static TargetLV2SpecHook* create(const ParameterSetDumpable& params);

			static TargetLV2SpecHook* create(ParameterSet&& params)=delete;


			const TargetLV2SpecFactory& factoryGet() const noexcept
				{return m_factory;}

			const TargetLV2SpecLoader& loaderGet() const noexcept
				{return m_loader;}

			void configClear();

			TargetLV2SpecHook& configAppendDefault();

			TargetLV2SpecHook& configAppend(const ResourceObject& lv2specoptions);

			void configDump(ResourceObject& lv2specoptions) const;

		private:
			TargetLV2SpecCompiler m_intpret;
			TargetLV2SpecLoader m_loader;
			TargetLV2SpecFactory m_factory;

			explicit TargetLV2SpecHook(const ParameterSetDumpable& params);

			void destroy() noexcept;
		};
	}

#endif
