//@	{"targets":[{"name":"feature_descriptor.hpp","type":"include"}]}

#ifndef LV2PLUG_FEATUREDESCRIPTOR_HPP
#define LV2PLUG_FEATUREDESCRIPTOR_HPP

#include "visibility.hpp"

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>

namespace LV2Plug
	{
	static constexpr uint64_t OFFSET_BASIS=0xcbf29ce484222325;
	static constexpr uint64_t FNV_PRIME=0x100000001b3;
	static constexpr uint64_t hash(const char* str,uint64_t value_init=OFFSET_BASIS)
		{return *str=='\0'?value_init:hash(str+1, (value_init^(uint64_t(*str)))*FNV_PRIME);}

	inline constexpr uint64_t make_key(const char* str)
		{return hash(str);}

	namespace
		{
		template<class T,size_t N>
		struct ArrayFixed
			{
			T content[N];
			static constexpr size_t size() noexcept
				{return N;}
			};
		 
		template<class ConstArray>
		constexpr ArrayFixed<uint64_t,ConstArray::size()> hash_array()
			{
			ArrayFixed<uint64_t,ConstArray::size()> ret{};
			for(size_t k=0;k<ConstArray::size();++k)
				{ret.content[k]=make_key(ConstArray::get(k));}
			return ret;
			}
		}

	template<class FeatureRequest>
	class PRIVATE FeatureDescriptor
		{
		public:
			typedef uint64_t Key;

			FeatureDescriptor(const FeatureDescriptor&)=default;
			FeatureDescriptor& operator=(const FeatureDescriptor&)=default;
			FeatureDescriptor(FeatureDescriptor&&)=default;
			FeatureDescriptor& operator=(FeatureDescriptor&&)=default;
	  
			explicit FeatureDescriptor(const LV2_Feature* const* features)
				{
				const LV2_URID_Map* feature_map=nullptr;
				while(*features!=nullptr)
					{
					if(!strcmp((*features)->URI,LV2_URID__map))
						{
						feature_map=(LV2_URID_Map*) (*features)->data;
						break;
						}
					++features;
					}
				if(feature_map==nullptr)
					{throw "LV2Plug: Failed to initialize plugin: urid:map unsupported by host";}

				for(size_t k=0;k<FeatureRequest::size();++k)
					{m_id[k]=feature_map->map(feature_map->handle,FeatureRequest::get(k));}
				}	

			template<Key key>
			LV2_URID get()
				{return m_id[Find<key>::index];}
	  
		private:
			LV2_URID m_id[FeatureRequest::size()];
	  
			static constexpr ArrayFixed<Key,FeatureRequest::size()> s_keys=hash_array<FeatureRequest>();

			template<Key key,size_t N=s_keys.size(),bool found=false>
			struct Find
				{
				static constexpr size_t index=Find<key,N-1,s_keys.content[N-1]==key>::index;
				typedef typename Find<key,N-1,s_keys.content[N-1]==key>::IndexType IndexType;
				};

			template<Key key>
			struct Find<key,0,false>
				{
				typedef void IndexType;
				};

			template<Key key,size_t N>
			struct Find<key,N,true>
				{
				static constexpr size_t index=N;
				typedef size_t IndexType;
				};
		};
	}
#endif
