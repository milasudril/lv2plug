//@	{"targets":[{"name":"portmap.hpp","type":"include"}]}

#ifndef LV2PLUG_PORTMAP_HPP
#define LV2PLUG_PORTMAP_HPP

#include <cassert>
#include <type_traits>

namespace LV2Plug
	{
	template<class PortDescriptor>
	class PortMap
		{
		public:
			template<unsigned int port_id>
			auto get() noexcept
				{
				static_assert(port_id < portCountGet(),"Bad port number");

				typedef typename PortDescriptor::template TypeGet<port_id>::type RetType;

				return valueGet<RetType>(port_id);
				}

			PortMap& connect(unsigned int port_index,void* buffer) noexcept
				{
				assert(port_index<portCountGet());
				ports[port_index]=buffer;
				return *this;
				}

			static constexpr unsigned int portCountGet() noexcept
				{
				return PortDescriptor::PORT_COUNT;
				}

		private:
			void* ports[portCountGet()];

			template<class T>
			std::enable_if_t<std::is_pointer<T>::value,T> valueGet(unsigned int port_id) noexcept
				{return reinterpret_cast<T>(ports[port_id]);}

			template<class T>
			std::enable_if_t<!std::is_pointer<T>::value,T> valueGet(unsigned int port_id) noexcept
				{return *reinterpret_cast<T*>(ports[port_id]);}
		};
	}

#endif
