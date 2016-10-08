//@	{
//@	 "targets":[{"name":"targetlv2specfactory.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"targetlv2specfactory.o","rel":"implementation"}]
//@	}

#ifndef MAIKE_TARGETLV2SPECFACTORY_HPP
#define MAIKE_TARGETLV2SPECFACTORY_HPP

#include <maike/target_factory.hpp>
#include "targetlv2spec.hpp"

namespace Maike
	{
	class TargetLV2SpecCompiler;

	class PRIVATE TargetLV2SpecFactory:public Target_Factory
		{
		public:
			explicit TargetLV2SpecFactory(const TargetLV2SpecCompiler& intptret);
			TargetLV2SpecFactory(TargetLV2SpecCompiler&&)=delete;

			Handle<Target> targetCreate(const ResourceObject& obj
				,const char* name_src,const char* in_dir,const char* root	
				,size_t id,size_t line_count) const;

		private:
			const TargetLV2SpecCompiler& r_intpret;
		};
	}

#endif
