#ifdef __WAND__
target[name[main.o] type[object]]
#endif

#include "main.h"
#include "client.h"

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
