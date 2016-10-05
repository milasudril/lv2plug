//@	{
//@	    "dependencies_extra":[],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"client.hpp",
//@	            "type":"include"
//@	        }
//@	    ]
//@	}
#ifndef LV2PLUG_CLIENT_HPP
#define LV2PLUG_CLIENT_HPP

#include "feature_descriptor.hpp"
#include <cstdio>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

namespace LV2Plug
	{
	template<class Client>
	LV2_Handle create(const LV2_Descriptor* descriptor,double f_s
		,const char* path_bundle,const LV2_Feature* const* features)
		{
		try
			{
			return Client::create(f_s,path_bundle,FeatureDescriptor(features));
			}
		catch(const char* errstr)
			{printf("Error while initializing plugin: %s\n",errstr);}
		catch(...)
			{
			printf("Error while initializing plugin\n");
			}
		return nullptr;
		}
	
	template<class Client>
	void portConnect(LV2_Handle handle,uint32_t port,void* data)
		{static_cast<Client*>(handle)->portConnect(port,data);}
		
	template<class Client>
	void activate(LV2_Handle handle)
		{static_cast<Client*>(handle)->activate();}
	
	template<class Client>
	void process(LV2_Handle handle, uint32_t n_frames)
		{static_cast<Client*>(handle)->process(n_frames);}
	
	template<class Client>
	void deactivate(LV2_Handle handle)
		{static_cast<Client*>(handle)->deactivate();}
	
	template<class Client>
	void destroy(LV2_Handle handle)
		{static_cast<Client*>(handle)->destroy();}
		
	template<class Client>
	const void* extensionDataGet(const char* uri)
		{return Client::extensionDataGet(uri);}

	template<class Client>
	struct Descriptor
		{
		static const LV2_Descriptor descriptor;	
		};
	
	template<class Client>
	const LV2_Descriptor Descriptor<Client>::descriptor=
		{
		 Client::URI
		,create<Client>
		,portConnect<Client>
		,activate<Client>
		,process<Client>
		,deactivate<Client>
		,destroy<Client>
		,extensionDataGet<Client>
		};
		
	template<class Client>
	const LV2_Descriptor& descriptorGet()
		{return Descriptor<Client>::descriptor;}
	}

#endif
