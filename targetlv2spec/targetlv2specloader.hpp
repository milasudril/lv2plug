//@	{
//@	 "targets":[{"name":"targetlv2specloader.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2specloader.o","rel":"implementation"}]
//@	}

#ifndef TARGETLV2SPECLOADER_HPP
#define TARGETLV2SPECLOADER_HPP

#include <maike/target_loader.hpp>

namespace Maike
	{
	class TargetLV2SpecCompiler;

	class PRIVATE TargetLV2SpecLoader:public Target_Loader
		{
		public:
			explicit TargetLV2SpecLoader(const TargetLV2SpecCompiler& intpret);
			TargetLV2SpecLoader(TargetLV2SpecCompiler&&)=delete;

			void targetsLoad(const char* name_src,const char* in_dir
				,Spider& spider,DependencyGraph& graph
				,Target_FactoryDelegator& factory) const;

			void dependenciesExtraGet(const char*,const char*
				,const char*,ResourceObject::Reader
				,DependencyBuffer&) const
				{}

			void dependenciesGet(const char*,const char*
				,const char*,ResourceObject::Reader
				,DependencyBuffer&) const
				{} 

			Handle<Target> targetCreate(const ResourceObject& obj
				,const char* name_src,const char* in_dir,const char* root	
				,size_t id,size_t line_count) const;

		private:
			const TargetLV2SpecCompiler& r_intpret;
		};
	}

#endif
