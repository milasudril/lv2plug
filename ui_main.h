#ifdef __WAND__
target[name[ui_main.h] type[include]]
dependency[ui_main.o]
#endif

#ifndef LV2PLUG_UIMAIN_H
#define LV2PLUG_UIMAIN_H

//#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

namespace LV2Plug
	{
	const LV2UI_Descriptor& ui_main();
	}

#endif
