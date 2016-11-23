//@	{"targets":[{"name":"targetlv2specfactory.o","type":"object"}]}

#include "targetlv2specfactory.hpp"

using namespace Maike;

TargetLV2SpecFactory::TargetLV2SpecFactory(const TargetLV2SpecCompiler& intpret):
	r_intpret(intpret)
	{}

Handle<Target> TargetLV2SpecFactory::targetCreate(const ResourceObject& obj
	,const char* name_src,const char* in_dir,const char* root
	,size_t id,size_t line_count) const
	{
	return Handle<TargetLV2Spec>( TargetLV2Spec::create(obj,r_intpret,name_src,in_dir,root
		,id,line_count) );
	}
