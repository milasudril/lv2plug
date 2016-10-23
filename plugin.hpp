//@	{
//@	"targets":[{"name":"plugin.hpp","type":"include"}]
//@	}

#ifndef LV2PLUG_PLUGIN_HPP
#define LV2PLUG_PLUGIN_HPP

#include "portmap.hpp"
#include "visibility.hpp"

namespace LV2Plug
	{
	template<class PluginDescriptor>
	class PRIVATE Plugin
		{
		public:
			typedef typename PluginDescriptor::Ports Ports;

			template<unsigned int port_id>
			using Port=typename PluginDescriptor::template Port<port_id>;

			auto& portmap() noexcept
				{return m_ports;}

			const auto& portmap() const noexcept
				{return m_ports;}

			static constexpr PluginDescriptor descriptor() noexcept
				{return PluginDescriptor{};}

			static constexpr void* extensionDataGet(const char*) noexcept
				{return nullptr;}

			constexpr void activate() noexcept
				{}

			constexpr void deactivate() noexcept
				{}

		private:
			PortMap<PluginDescriptor> m_ports;
		};
	}

#endif
