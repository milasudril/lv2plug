//@	{
//@	"targets":[{"name":"plugin_ui.hpp","type":"include"}]
//@	}

#ifndef LV2PLUG_PLUGINUI_HPP
#define LV2PLUG_PLUGINUI_HPP

#include "visibility.hpp"
#include "uicontroller.hpp"

namespace LV2Plug
	{
	template<class PluginDescriptor>
	class PRIVATE PluginUI
		{
		public:
			typedef PluginUI Base;

			typedef typename PluginDescriptor::Ports Ports;

			static constexpr PluginDescriptor descriptor() noexcept
				{return PluginDescriptor{};}

			static constexpr void* extensionDataGet(const char*) noexcept
				{return nullptr;}

			constexpr portEvent(uint32_t port,uint32_t buffer_size,uint32_t format
				,const void* data) noexcept
				{}

			PluginUI(const UIController& ctrl):m_ctrl(ctrl)
				{}

		private:
			UIController m_ctrl;
		};
	}

#endif
