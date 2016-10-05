//@	{
//@	    "dependencies_extra":[],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"main.o",
//@	            "type":"object"
//@	        }
//@	    ]
//@	}
#include "main.hpp"
#include "client.hpp"

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index)
	{
	switch (index)
		{
		case 0:
			return &LV2Plug::main();
		default:
			return nullptr;
		}
	}
