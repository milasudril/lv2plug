//@	{"targets":[{"name":"targetlv2specloader.o","type":"object"}]}

#include "targetlv2specloader.hpp"
#include "targetlv2spec.hpp"
#include <maike/readbuffer.hpp>
#include <maike/filein.hpp>
#include <maike/resourceobject.hpp>
#include <maike/exceptionhandler.hpp>
#include <maike/errormessage.hpp>
#include <maike/variant.hpp>
#include <maike/target_factorydelegator.hpp>
#include <maike/spider.hpp>

using namespace Maike;

TargetLV2SpecLoader::TargetLV2SpecLoader(const TargetLV2SpecCompiler& intpret):
	r_intpret(intpret)
	{}

namespace
	{
	class TagExtractor final:public Target_FactoryDelegator::TagExtractor
		{
		public:
			TagExtractor(DataSource& source):m_reader(source),m_lines(0)
				{}

			size_t read(void* buffer,size_t length);

			const char* nameGet() const noexcept
				{return m_reader.nameGet();}

			size_t linesCountGet() const noexcept
				{return m_lines;}

		private:
			ReadBuffer m_reader;
			size_t m_lines;

			void destroy()
				{delete this;}
		};
	}

size_t TagExtractor::read(void* buffer,size_t length)
	{
	auto buffer_out=reinterpret_cast<uint8_t*>(buffer);
	size_t n_read=0;
	while(n_read!=length && !m_reader.eof())
		{
		auto ch_in=m_reader.byteRead();
		if(ch_in=='\n')
			{++m_lines;}
		*buffer_out=ch_in;
		++n_read;
		++buffer_out;
		}
	return n_read;
	}

void TargetLV2SpecLoader::targetsLoad(const char* name_src,const char* in_dir
	,Spider& spider,DependencyGraph& graph,Target_FactoryDelegator& factory) const
	{
	FileIn source(name_src);
	TagExtractor extractor(source);
	factory.targetsCreate(extractor,name_src,in_dir,*this,spider,graph);
	}

Handle<Target> TargetLV2SpecLoader::targetCreate(const ResourceObject& obj
	,const char* name_src,const char* in_dir,const char* root	
	,size_t id,size_t line_count) const
	{
	return Handle<TargetLV2Spec>( TargetLV2Spec::create(obj,r_intpret,name_src,in_dir,root
		,id,line_count) );
	}