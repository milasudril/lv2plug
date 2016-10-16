//@	{
//@	"targets":
//@		[{
//@		"name":"monosynth-gtk.so","type":"lib_dynamic"
//@		,"dependencies":
//@			[{"ref":"lv2plug_ui","rel":"external"}]
//@		,"pkgconfig_libs":["gtk+-2.0"]
//@		}]
//@	}

#include <maike/targetinclude.hpp>

#include MAIKE_TARGET(plugindescriptor.hpp)

#include <lv2plug/lv2plug_ui.hpp>
#include <gtk/gtk.h>

class PRIVATE GtkUI:public LV2Plug::PluginUI<MonophonicSynth::PluginDescriptor>
	{
	public:
		GtkUI(const char* path_bundle,const LV2Plug::UIController& controller
			,LV2Plug::FeatureDescriptor&& features):Base(controller),m_features(features)
			{
			m_widget=gtk_button_new_with_label(descriptor().nameGet());
			gtk_widget_show(m_widget);
			}

		~GtkUI()
			{}

		void* widgetGet() noexcept
			{return m_widget;}

	private:
		LV2Plug::FeatureDescriptor m_features;
		GtkWidget* m_widget;
	};

const LV2UI_Descriptor& LV2Plug::mainUI()
	{
	return LV2Plug::descriptorUiGet<GtkUI>();
	}
