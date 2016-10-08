//@	{
//@  "targets":[{"name":"targetlv2speccompiler.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2speccompiler.o","rel":"implementation"}]
//@	}

#ifndef MAIKE_TARGETLV2SPECCOMPILER_HPP
#define MAIKE_TARGETLV2SPECCOMPILER_HPP

#include <maike/command.hpp>

namespace Maike
	{
	class ResourceObject;
	class ParameterSetDumpable;
	class PRIVATE TargetLV2SpecCompiler
		{
		public:
			explicit TargetLV2SpecCompiler(const ParameterSetDumpable& sysvars);

			explicit TargetLV2SpecCompiler(ParameterSetDumpable&& sysvars)=delete;

			TargetLV2SpecCompiler(const ResourceObject& lv2specoptions
				,ParameterSet&& sysvars)=delete;

			void compileTTL(const char* source) const;
			void compileHPP(const char* source) const;

			void configClear();

			TargetLV2SpecCompiler& configAppendDefault();

			TargetLV2SpecCompiler& configAppend(const ResourceObject& lv2specoptions);

			void configDump(ResourceObject& lv2specoptions) const;

		private:
			Command m_tottler;
			Command m_tohopper;
			const ParameterSetDumpable& r_sysvars;
		};
	}

#endif
