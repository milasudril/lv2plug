//@	{
//@	"targets":[{"name":"plugin_ui.hpp","type":"include"}]
//@	}

#ifndef LV2PLUG_PLUGINUI_HPP
#define LV2PLUG_PLUGINUI_HPP

#include "visibility.hpp"
#include "uicontroller.hpp"
#include <type_traits>

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

			PluginUI(const UIController& ctrl):m_ctrl(ctrl)
				{}

			template<unsigned int port>
			static constexpr const char* portNameGet() noexcept
				{
				static_assert(port<Ports::PORT_COUNT,"Bad port number");
				return Ports::PORTNAMES[port];
				}

		protected:
			template<unsigned int port>
			void portWrite(typename Ports::template TypeGet<port>::type value) noexcept
				{m_ctrl.write(value,port);}

		private:
			UIController m_ctrl;
		};

	template<unsigned int PortNumber,class ClientUI>
	using PortType=typename ClientUI::Ports::template TypeGet<PortNumber>::type;
	}

template<unsigned int PortNumber,class ClientUI>
void PRIVATE update(ClientUI& ui
	,std::enable_if_t<!std::is_pointer< LV2Plug::PortType<PortNumber,ClientUI> >::value
		,LV2Plug::PortType<PortNumber,ClientUI>> value){}

template<unsigned int PortNumber,class ClientUI>
void PRIVATE update(ClientUI& ui
	,std::enable_if_t<std::is_pointer< LV2Plug::PortType<PortNumber,ClientUI> >::value
		,const std::remove_pointer_t<LV2Plug::PortType<PortNumber,ClientUI>>* > value){}

#endif
