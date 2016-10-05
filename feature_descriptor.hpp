//@	{
//@	    "dependencies_extra":[
//@	        {
//@	            "ref":"feature_descriptor.o",
//@	            "rel":"implementation"
//@	        }
//@	    ],
//@	    "targets":[
//@	        {
//@	            "dependencies":[],
//@	            "name":"feature_descriptor.hpp",
//@	            "type":"include"
//@	        }
//@	    ]
//@	}
#ifndef LV2PLUG_FEATUREDESCRIPTOR_HPP
#define LV2PLUG_FEATUREDESCRIPTOR_HPP

#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

namespace LV2Plug
	{
	class FeatureDescriptor
		{
		public:
			FeatureDescriptor(const FeatureDescriptor&)=default;
			FeatureDescriptor& operator=(const FeatureDescriptor&)=default;
			FeatureDescriptor(FeatureDescriptor&&)=default;
			FeatureDescriptor& operator=(FeatureDescriptor&&)=default;
			
			FeatureDescriptor(const LV2_Feature* const* features);
			
			LV2_URID midi() const
				{return id_MIDI;}
			
			LV2_URID AtomBlank() const
				{return id_AtomBlank;}
			
			LV2_URID AtomObject() const
				{return id_AtomObject;}
			
			LV2_URID AtomSeq() const
				{return id_AtomSeq;}
			
			LV2_URID Long() const
				{return id_Long;}
			
			LV2_URID Float() const
				{return id_Float;}
				
			LV2_URID Double() const
				{return id_Double;}
			
			LV2_URID position() const
				{return id_Position;}
				
			LV2_URID barBeat() const
				{return id_barBeat;}
				
			LV2_URID Beat() const
				{return id_Beat;}
				
			LV2_URID beatsPerMinute() const
				{return id_beatsPerMinute;}
				
			LV2_URID speed() const
				{return id_speed;}
			
			LV2_URID frame() const
				{return id_frame;}
			
			LV2_URID fps() const
				{return id_fps;}
				
			
		private:
			LV2_URID id_MIDI;
			LV2_URID id_AtomBlank         ;
			LV2_URID id_AtomObject        ;
			LV2_URID id_AtomSeq           ;
			LV2_URID id_Long              ;
			LV2_URID id_Float             ;
			LV2_URID id_Double            ;
			LV2_URID id_Position          ;
			LV2_URID id_barBeat           ;
			LV2_URID id_Beat              ;
			LV2_URID id_beatsPerMinute    ;
			LV2_URID id_speed             ;
			LV2_URID id_frame             ;
			LV2_URID id_fps               ;
		};
	};

#endif
