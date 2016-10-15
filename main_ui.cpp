//@	{
//@	    "dependencies_extra":[],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"main_ui.o",
//@	            "type":"object"
//@	        }
//@	    ]
//@	}
#include "main_ui.hpp"
#include "client_ui.hpp"

LV2_SYMBOL_EXPORT const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
	{
	switch (index)
		{
		case 0:
			return &LV2Plug::mainUI();
		default:
			return nullptr;
		}
	}
