//@	[
//@		{
//@		"targets":
//@			[{
//@			 "name":"../targetlv2spec.so","type":"lib_dynamic"
//@			,"dependencies":
//@				[{"ref":"pthread","rel":"external"}
//@				,{"ref":"maikeplug","rel":"external"}]
//@			}]
//@		}
//@	]

#include "targetlv2spechook.hpp"
#include <maike/exceptionhandler.hpp>
#include <maike/stdstream.hpp>

using namespace Maike;

void Maike_Plugin_init(DataSink& standard_output,DataSink& standard_error
	,ExceptionHandler eh)
	{
	exceptionHandlerSet(eh);
	StdStream::outputSet(standard_output);
	StdStream::errorSet(standard_error);
	}

void Maike_Plugin_cleanup()
	{}

Target_Hook* Maike_Target_Hook_create(const ParameterSetDumpable& params)
	{
	return TargetLV2SpecHook::create(params);
	}
