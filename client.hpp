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
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <limits>
#include <cstdio>

namespace LV2Plug
	{
	template<class Client>
	LV2_Handle create(const LV2_Descriptor* descriptor,double f_s
		,const char* path_bundle,const LV2_Feature* const* features)
		{
		try
			{
			return new Client(f_s,path_bundle
				,FeatureDescriptor<typename Client::FeatureRequest>(features));
			}

		catch(const char* errstr)
			{fprintf(stderr,"%s: %s\n",Client::descriptor().name(),errstr);}
		catch(...)
			{fprintf(stderr,"%s: Initialization failed\n",Client::descriptor().name());}

		return nullptr;
		}

	template<class Client>
	void portConnect(LV2_Handle handle,uint32_t port,void* data)
		{
		auto client=reinterpret_cast<Client*>(handle);
		auto& portmap=client->portmap();
		constexpr auto N_ports=portmap.portCountGet();
		if(port>=N_ports)
			{
			fprintf(stderr,"%s has only %u ports",Client::descriptor().name(),N_ports);
			return;
			}
		portmap.connect(port,data);
		}

	template<class Client>
	void activate(LV2_Handle handle)
		{reinterpret_cast<Client*>(handle)->activate();}

	template<class Client>
	void process(LV2_Handle handle, uint32_t n_frames)
		{reinterpret_cast<Client*>(handle)->process(n_frames);}

	template<class Client>
	void deactivate(LV2_Handle handle)
		{reinterpret_cast<Client*>(handle)->deactivate();}

	template<class Client>
	void destroy(LV2_Handle handle)
		{delete reinterpret_cast<Client*>(handle);}

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
		 Client::descriptor().uri()
		,create<Client>
		,portConnect<Client>
		,activate<Client>
		,process<Client>
		,deactivate<Client>
		,destroy<Client>
		,extensionDataGet<Client>
		};

	template<class Client>
	inline const LV2_Descriptor& descriptorGet()
		{
	//	Force the linker to export lv2_descriptor, by calling it with highvalue.
	//	This will not have any side effect (returns nullptr). Hopefully, the
	//	linker isn't smart enougth...
		lv2_descriptor(std::numeric_limits<uint32_t>::max());
		return Descriptor<Client>::descriptor;
		}
	}

#endif
