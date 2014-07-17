#ifdef __WAND__
target[name[ui.h] type [include]]
#endif

#ifndef LV2PLUG_UI_H
#define LV2PLUG_UI_H

#include "feature_descriptor.h"
#include <cstdio>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

namespace LV2Plug
	{
	template<class Ui>
	LV2UI_Handle create(const LV2UI_Descriptor* descriptor
		,const char* plugin_uri
		,const char* path_bundle
		,LV2UI_Write_Function write_callback
		,LV2UI_Controller controller
		,LV2UI_Widget* widget
		,const LV2_Feature* const* features)
		{
		try
			{
			return Ui::create(path_bundle,write_callback,controller
				,widget,FeatureDescriptor(features));
			}
		catch(const char* errstr)
			{printf("Error while initializing plugin: %s\n",errstr);}
		catch(...)
			{
			printf("Error while initializing plugin\n");
			}
		return nullptr;
		}
	
	template<class Ui>
	void portEvent(LV2UI_Handle handle,uint32_t port,uint32_t buffer_size
		,uint32_t format,const void* buffer)
		{
		static_cast<Ui*>(handle)->portEvent(port,buffer_size,format,buffer);
		}
	
	template<class Ui>
	void destroy(LV2UI_Handle handle)
		{static_cast<Ui*>(handle)->destroy();}

	template<class Ui>
	struct Descriptor
		{
		static const LV2UI_Descriptor descriptor;	
		};
	
	template<class Ui>
	const LV2UI_Descriptor Descriptor<Ui>::descriptor=
		{
		 Ui::URI
		,create<Ui>
		,destroy<Ui>
		,portEvent<Ui>
		,NULL
		};
		
	template<class Ui>
	const LV2UI_Descriptor& descriptorGet()
		{return Descriptor<Ui>::descriptor;}
	}

#endif
