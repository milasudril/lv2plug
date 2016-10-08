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

#include "visibility.hpp"
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

			PRIVATE FeatureDescriptor(const LV2_Feature* const* features);

			LV2_URID midi() const noexcept
				{return id_MIDI;}

			LV2_URID AtomBlank() const noexcept
				{return id_AtomBlank;}

			LV2_URID AtomObject() const noexcept
				{return id_AtomObject;}

			LV2_URID AtomSeq() const noexcept
				{return id_AtomSeq;}

			LV2_URID Long() const noexcept
				{return id_Long;}

			LV2_URID Float() const noexcept
				{return id_Float;}

			LV2_URID Double() const noexcept
				{return id_Double;}

			LV2_URID position() const noexcept
				{return id_Position;}

			LV2_URID barBeat() const noexcept
				{return id_barBeat;}

			LV2_URID Beat() const noexcept
				{return id_Beat;}

			LV2_URID beatsPerMinute() const noexcept
				{return id_beatsPerMinute;}

			LV2_URID speed() const noexcept
				{return id_speed;}

			LV2_URID frame() const noexcept
				{return id_frame;}

			LV2_URID fps() const noexcept
				{return id_fps;}


		private:
			LV2_URID id_MIDI;
			LV2_URID id_AtomBlank;
			LV2_URID id_AtomObject;
			LV2_URID id_AtomSeq;
			LV2_URID id_Long;
			LV2_URID id_Float;
			LV2_URID id_Double;
			LV2_URID id_Position;
			LV2_URID id_barBeat;
			LV2_URID id_Beat;
			LV2_URID id_beatsPerMinute;
			LV2_URID id_speed;
			LV2_URID id_frame;
			LV2_URID id_fps;
		};
	};

#endif
