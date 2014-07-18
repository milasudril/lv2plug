#ifdef __WAND__
target[name[feature_descriptor.o] type[object]]
#endif

#include "feature_descriptor.h"
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <cstring>

LV2Plug::FeatureDescriptor::FeatureDescriptor(const LV2_Feature* const* features)
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
		{throw "urid:map unsupported";}

	id_MIDI           = feature_map->map(feature_map->handle, LV2_MIDI__MidiEvent);
	id_AtomBlank      = feature_map->map(feature_map->handle, LV2_ATOM__Blank);
	id_AtomObject     = feature_map->map(feature_map->handle, LV2_ATOM__Object);
	id_AtomSeq        = feature_map->map(feature_map->handle, LV2_ATOM__Sequence);
	id_Long           = feature_map->map(feature_map->handle, LV2_ATOM__Long);
	id_Float          = feature_map->map(feature_map->handle, LV2_ATOM__Float);
	id_Double         = feature_map->map(feature_map->handle, LV2_ATOM__Double);
	id_Position       = feature_map->map(feature_map->handle, LV2_TIME__Position);
	id_barBeat        = feature_map->map(feature_map->handle, LV2_TIME__barBeat);
	id_Beat           = feature_map->map(feature_map->handle, LV2_TIME__beat);
	id_beatsPerMinute = feature_map->map(feature_map->handle, LV2_TIME__beatsPerMinute);
	id_speed          = feature_map->map(feature_map->handle, LV2_TIME__speed);
	id_frame          = feature_map->map(feature_map->handle, LV2_TIME__frame);
	id_fps            = feature_map->map(feature_map->handle, LV2_TIME__framesPerSecond);
	}