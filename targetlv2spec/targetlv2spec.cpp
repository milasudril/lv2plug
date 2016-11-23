//@	{"targets":[{"name":"targetlv2spec.o","type":"object"}]}

#include "targetlv2spec.hpp"
#include "targetlv2speccompiler.hpp"
#include <maike/resourceobject.hpp>
#include <maike/fileutils.hpp>

using namespace Maike;

TargetLV2Spec::TargetLV2Spec(const ResourceObject& obj
	,const TargetLV2SpecCompiler& compiler,const char* name_src
	,const char* in_dir,const char* root,size_t id,size_t line_count):
	TargetBase(obj,name_src,in_dir,root,id,line_count)
	,r_compiler(compiler)
	{}

void TargetLV2Spec::dumpDetails(ResourceObject& target) const
	{
	}

void TargetLV2Spec::compileImpl(Twins<const Dependency*> dependency_list
	,Twins<const Dependency*> dependency_list_full
	,const char* target_dir)
	{
	r_compiler.compileTTL(sourceNameGet());
	r_compiler.compileHPP(sourceNameGet());
	}

bool TargetLV2Spec::upToDate(Twins<const Dependency*> dependency_list
	,Twins<const Dependency*> dependency_list_full
	,const char* target_dir) const
	{
	auto name_full=dircat(target_dir,nameGet());
	if(FileUtils::newer(sourceNameGet(),name_full.c_str()))
		{return 0;}
	name_full=dircat(target_dir,"manifest.ttl");
	if(FileUtils::newer(sourceNameGet(),name_full.c_str()))
		{return 0;}
	return 1;
	}

Maike::TargetLV2Spec::~TargetLV2Spec() noexcept
	{
	}


TargetLV2Spec* TargetLV2Spec::create(const ResourceObject& obj
	,const TargetLV2SpecCompiler& intpret,const char* name_src
	,const char* in_dir,const char* root,size_t id,size_t line_count)
	{return new TargetLV2Spec(obj,intpret,name_src,in_dir,root,id,line_count);}

void TargetLV2Spec::destroy() noexcept
	{delete this;}
