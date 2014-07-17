#ifdef __WAND__
target[name[ui.h] type [include]]
#endif

#ifndef LV2PLUG_UI_H
#define LV2PLUG_UI_H

#include "feature_descriptor.h"
#include "lv2_external_ui.h"
#include <cstdio>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>
#include <cstring>

namespace LV2Plug
	{
	template<class T>
	class UiWrapper:public LV2_External_UI_Widget
		{
		public:
			static
			LV2UI_Handle doCreate(const LV2UI_Descriptor* descriptor
				,const char* plugin_uri
				,const char* path_bundle
				,LV2UI_Write_Function write_callback
				,LV2UI_Controller controller
				,LV2UI_Widget* widget
				,const LV2_Feature* const* features)
				{
				try
					{
					const LV2_External_UI_Host* ext_host=nullptr;
					while(*features!=nullptr)
						{
						if(!strcmp((*features)->URI,LV2_EXTERNAL_UI__Host))
							{
							ext_host=(const LV2_External_UI_Host*) (*features)->data;
							break;
							}
						++features;
						}
					if(ext_host==nullptr)
						{throw "External UI unsupported!\n";}
						
					*widget=T::doCreate(path_bundle,write_callback,controller
						,*ext_host);
					return widget;
					}
				catch(const char* errstr)
					{printf("Error while initializing plugin: %s\n",errstr);}
				catch(...)
					{
					printf("Error while initializing plugin\n");
					}
				return nullptr;
				}
				
			static
			const LV2UI_Descriptor& uiDescriptorGet()
				{return descriptor;}
		
		protected:
			UiWrapper()
				{
				run=doRun;
				show=doShow;
				hide=doHide;
				}
	
		private:
			static const LV2UI_Descriptor descriptor;
			
			static void doPortEvent(LV2UI_Handle handle,uint32_t port
				,uint32_t buffer_size,uint32_t format,const void* buffer)
				{
				static_cast<T*>(handle)->doPortEvent(port,buffer_size,format,buffer);
				}
	
			static void doDestroy(LV2UI_Handle handle)
				{static_cast<T*>(handle)->doDestroy();}
		
			static void doRun(LV2_External_UI_Widget* handle)
				{static_cast<T*>(handle)->doRun();}
	
			static void doShow(LV2_External_UI_Widget* handle)
				{static_cast<T*>(handle)->doShow();}
		
			static void doHide(LV2_External_UI_Widget* handle)
				{static_cast<T*>(handle)->doHide();}
		};
	
	template<class T>
	const LV2UI_Descriptor UiWrapper<T>::descriptor=
		{
		T::URI
		,doCreate
		,doDestroy
		,doPortEvent
		,NULL
		};
	}

#endif
