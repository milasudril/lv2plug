//@	{"targets":[{"name":"targetlv2speccompiler.o","type":"object"}]}

#include "targetlv2speccompiler.hpp"
#include <maike/resourceobject.hpp>
#include <maike/parametersetmapfixed.hpp>
#include <maike/readbuffer.hpp>
#include <maike/errormessage.hpp>
#include <maike/variant.hpp>
#include <maike/exceptionhandler.hpp>
#include <maike/thread.hpp>
#include <maike/parametersetdumpable.hpp>
#include <maike/stdstream.hpp>
#include <maike/writebuffer.hpp>


using namespace Maike;

TargetLV2SpecCompiler::TargetLV2SpecCompiler(const ParameterSetDumpable& sysvars)
	:r_sysvars(sysvars)
	{
	configClear();
	}


namespace
	{
	class ReadCallback
		{
		public:
			explicit ReadCallback(DataSource* src):r_src(src)
				{}

			void operator()()
				{
				WriteBuffer wb(StdStream::error());
				try
					{
					ReadBuffer rb(*r_src);
					while(!rb.eof())
						{
						wb.write(rb.byteRead());
						}
					}
				catch(const ErrorMessage& message)
					{wb.write("Error: ").write(message.messageGet());}
				}

		private:
			DataSource* r_src;
		};
	}

static void dataProcess(Pipe& compiler,const ParameterSetDumpable& sysvars)
	{
	auto standard_error=compiler.stderrCapture();
	Thread<ReadCallback> stderr_reader(ReadCallback{standard_error.get()});
	}

void TargetLV2SpecCompiler::compileTTL(const char* source) const
	{
	ParameterSetMapFixed<Stringkey("source")> params;
	params.get<Stringkey("source")>().push_back(source);
	const ParameterSet* paramset_tot[]={&params,&r_sysvars};
	auto pipe=m_tottler.execute(Pipe::REDIRECT_STDERR,{paramset_tot,paramset_tot+2});
	dataProcess(pipe,r_sysvars);
	auto ret=pipe.exitStatusGet();
	if(ret!=0)
		{exceptionRaise(ErrorMessage("#0;: It was not possible to create LV2 manifest file",{source}));}
	}

void TargetLV2SpecCompiler::compileHPP(const char* source) const
	{
	ParameterSetMapFixed<Stringkey("source")> params;
	params.get<Stringkey("source")>().push_back(source);
	const ParameterSet* paramset_tot[]={&params,&r_sysvars};
	auto pipe=m_tohopper.execute(Pipe::REDIRECT_STDERR,{paramset_tot,paramset_tot+2});
	dataProcess(pipe,r_sysvars);
	auto ret=pipe.exitStatusGet();
	if(ret!=0)
		{exceptionRaise(ErrorMessage("#0;: It was not possible to create plugin descriptor file",{source}));}
	}

void TargetLV2SpecCompiler::configClear()
	{
	m_tottler.nameSet("").argumentsClear();
	m_tohopper.nameSet("").argumentsClear();
	}

TargetLV2SpecCompiler& TargetLV2SpecCompiler::configAppendDefault()
	{
	configClear();
	m_tottler.nameSet("lv2spectottl.php").argumentAppend("{source}")
		.argumentAppend("{target_directory}");
	m_tohopper.nameSet("lv2spectohpp.php").argumentAppend("{source}")
		.argumentAppend("{target_directory}");
	return *this;
	}

TargetLV2SpecCompiler& TargetLV2SpecCompiler::configAppend(const ResourceObject& lv2specoptions)
	{
	if(lv2specoptions.objectExists("tottler"))
		{m_tottler=Command(lv2specoptions.objectGet("tottler"));}
	if(lv2specoptions.objectExists("tohopper"))
		{m_tohopper=Command(lv2specoptions.objectGet("tohopper"));}
	return *this;
	}

void TargetLV2SpecCompiler::configDump(ResourceObject& lv2specoptions) const
	{
		{
		auto tottler=lv2specoptions.createObject();
		m_tottler.configDump(tottler);
		lv2specoptions.objectSet("tottler",std::move(tottler));
		}

		{
		auto tohopper=lv2specoptions.createObject();
		m_tohopper.configDump(tohopper);
		lv2specoptions.objectSet("tohopper",std::move(tohopper));
		}
	}
