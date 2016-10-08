//@	{
//@	 "targets":[{"name":"targetlv2spec.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2spec.o","rel":"implementation"}]
//@	}

#ifndef MAIKE_TARGETLV2SPECSOURCE_HPP
#define MAIKE_TARGETLV2SPECSOURCE_HPP

#include <maike/targetbase.hpp>

namespace Maike
	{
	class TargetLV2SpecCompiler;
	class PRIVATE TargetLV2Spec final : public Maike::TargetBase
		{
		public:
			static TargetLV2Spec* create(const ResourceObject& obj
				,const TargetLV2SpecCompiler& compiler,const char* name_src
				,const char* in_dir,const char* root,size_t id,size_t line_count);

			static TargetLV2Spec* create(const ResourceObject& obj
				,TargetLV2SpecCompiler&& compiler,const char* name_src
				,const char* in_dir,const char* root,size_t id
				,size_t line_count)=delete;

			bool upToDate(Twins<const Dependency*> dependency_list
				,Twins<const Dependency*> dependency_list_full
				,const char* target_dir) const;

			void compileImpl(Twins<const Dependency*> dependency_list
				,Twins<const Dependency*> dependency_list_full
				,const char* target_dir);

			void destroy() noexcept;

			void dumpDetails(ResourceObject& target) const;

		private:
			const TargetLV2SpecCompiler& r_compiler;

			TargetLV2Spec(const ResourceObject& obj
				,const TargetLV2SpecCompiler& intpret,const char* name_src
				,const char* in_dir,const char* root,size_t id,size_t line_count);

			TargetLV2Spec(const ResourceObject& obj
				,TargetLV2SpecCompiler&& intpret,const char* name_src
				,const char* in_dir,const char* root,size_t id
				,size_t line_count)=delete;

			~TargetLV2Spec() noexcept;
		};
	}

#endif
