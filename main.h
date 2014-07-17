#ifdef __WAND__
target[name[main.h] type[include]]
dependency[main.o]
#endif

#ifndef LV2PLUG_MAIN_H
#define LV2PLUG_MAIN_H

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

namespace LV2Plug
	{
	const LV2_Descriptor& main();
	}

#endif
