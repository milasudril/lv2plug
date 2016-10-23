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
			auto box=reinterpret_cast<GtkBox*>(gtk_vbox_new(FALSE,0));
			m_box=reinterpret_cast<GtkWidget*>(box);
			auto label=gtk_label_new(
				Port<MonophonicSynth::PluginDescriptor::Ports::CUTOFF>::name()
				);
			gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(label),0,0,0);

			auto cutoff=gtk_vscale_new_with_range(Port<MonophonicSynth::PluginDescriptor::Ports::CUTOFF>::minimum()
				,Port<MonophonicSynth::PluginDescriptor::Ports::CUTOFF>::maximum(),1e-7f);
			m_cutoff=cutoff;
			gtk_scale_set_draw_value(reinterpret_cast<GtkScale*>(cutoff),0);
			g_signal_connect(cutoff,"value_changed",G_CALLBACK(cutoff_update),this);
			gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(cutoff),1,1,0);
			
			gtk_widget_show(m_cutoff);
			gtk_widget_show(reinterpret_cast<GtkWidget*>(label));
			gtk_widget_show(m_box);
			}

		~GtkUI()
			{gtk_widget_destroy(m_box);}

		void* widgetGet() noexcept
			{return m_box;}

		void sliderPositionSet(float value)
			{
			value=1.0f - value;
			gtk_range_set_value(reinterpret_cast<GtkRange*>(m_cutoff),value);
			}

	private:
		static void cutoff_update(GtkAdjustment *adj,void* gtkui)
			{
			auto self=reinterpret_cast<GtkUI*>(gtkui);
			auto v=1.0 - gtk_range_get_value(reinterpret_cast<GtkRange*>(self->m_cutoff));
			self->portWrite<Ports::CUTOFF>(v);
			}

		LV2Plug::FeatureDescriptor m_features;
		GtkWidget* m_box;
		GtkWidget* m_cutoff;
	};

const LV2UI_Descriptor& LV2Plug::mainUI()
	{
	return LV2Plug::descriptorUiGet<GtkUI>();
	}

template<>
void update<GtkUI::Ports::CUTOFF>(GtkUI& ui,float value)
	{ui.sliderPositionSet(value);}
