//@	{
//@	 "targets":[{"name":"targetlv2specloader.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2specloader.o","rel":"implementation"}]
//@	}

#ifndef TARGETLV2SPECLOADER_HPP
#define TARGETLV2SPECLOADER_HPP

#include <maike/target_loader.hpp>

namespace Maike
	{
	class PRIVATE TargetLV2SpecLoader:public Target_Loader
		{
		public:
			TargetLV2SpecLoader();

			void targetsLoad(const char* name_src,const char* in_dir
				,Spider& spider,DependencyGraph& graph
				,Target_FactoryDelegator& factory) const;

		private:
		};
	}

#endif
