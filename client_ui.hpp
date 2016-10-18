//@	{
//@	    "dependencies_extra":[],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"client_ui.hpp",
//@	            "type":"include"
//@	        }
//@	    ]
//@	}
#ifndef LV2PLUG_CLIENTUI_HPP
#define LV2PLUG_CLIENTUI_HPP

#include "feature_descriptor.hpp"
#include "uicontroller.hpp"
#include "uinotifier.hpp"
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>
#include <limits>
#include <cstdio>

namespace LV2Plug
	{
	template<class ClientUI>
	LV2UI_Handle create(const LV2UI_Descriptor* descriptor
		,const char* plugin_uri
		,const char* path_bundle
		,LV2UI_Write_Function write_function
		,LV2UI_Controller controller,LV2UI_Widget* widget
		,const LV2_Feature* const* features)
		{
		try
			{
			auto ui=new ClientUI(path_bundle,UIController(controller,write_function),FeatureDescriptor(features));
			*widget=ui->widgetGet();
			return ui;
			}
		catch(const char* errstr)
			{fprintf(stderr,"%s: %s\n",ClientUI::descriptor().nameGet(),errstr);}
		catch(...)
			{
			fprintf(stderr,"%s: Initialization failed\n",ClientUI::descriptor().nameGet());
			}
		return nullptr;
		}

	template<class ClientUI>
	void portEvent(LV2UI_Handle handle,uint32_t port,uint32_t buffer_size,uint32_t format
	,const void* data)
		{
		auto ui=reinterpret_cast<ClientUI*>(handle);
		UINotifier<ClientUI>::call(*ui,port,data);
		}

	template<class ClientUI>
	void destroy(LV2UI_Handle handle)
		{delete reinterpret_cast<ClientUI*>(handle);}

	template<class ClientUI>
	const void* extensionDataGet(const char* uri)
		{return ClientUI::extensionDataGet(uri);}

	template<class ClientUI>
	struct DescriptorUI
		{
		static const LV2UI_Descriptor descriptor;
		};

	template<class ClientUI>
	const LV2UI_Descriptor DescriptorUI<ClientUI>::descriptor=
		{
		 ClientUI::descriptor().uiUriGet()
		,create<ClientUI>
		,destroy<ClientUI>
		,portEvent<ClientUI>
		,extensionDataGet<ClientUI>
		};

	template<class ClientUI>
	inline const LV2UI_Descriptor& descriptorUiGet()
		{
	//	Force the linker to export lv2ui_descriptor, by calling it with highvalue.
	//	This will not have any side effect (returns nullptr). Hopefully, the
	//	linker isn't smart enougth...
		lv2ui_descriptor(std::numeric_limits<uint32_t>::max());
		return DescriptorUI<ClientUI>::descriptor;
		}
	}

#endif
