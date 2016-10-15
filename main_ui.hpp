//@	{
//@	    "dependencies_extra":[
//@	        {
//@	            "ref":"main_ui.o",
//@	            "rel":"implementation"
//@	        }
//@	    ],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"main_ui.hpp",
//@	            "type":"include"
//@	        }
//@	    ]
//@	}
#ifndef LV2PLUG_MAINUI_HPP
#define LV2PLUG_MAINUI_HPP

#include "visibility.hpp"
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

namespace LV2Plug
	{
	PRIVATE const LV2UI_Descriptor& mainUI();
	}

#endif
