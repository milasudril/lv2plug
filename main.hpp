//@	{
//@	    "dependencies_extra":[
//@	        {
//@	            "ref":"main.o",
//@	            "rel":"implementation"
//@	        }
//@	    ],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"main.hpp",
//@	            "type":"include"
//@	        }
//@	    ]
//@	}
#ifndef LV2PLUG_MAIN_HPP
#define LV2PLUG_MAIN_HPP

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

namespace LV2Plug
	{
	const LV2_Descriptor& main();
	}

#endif
