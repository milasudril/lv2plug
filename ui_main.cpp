#ifdef __WAND__
target[name[ui_main.o] type[object]]
#endif

#include "ui_main.h"
#include "ui.h"

LV2_SYMBOL_EXPORT const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index)
	{
	switch (index)
		{
		case 0:
			return &LV2Plug::ui_main();
		default:
			return nullptr;
		}
	}
