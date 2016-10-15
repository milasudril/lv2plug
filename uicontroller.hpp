//@	{"targets":[{"name":"uicontroller.hpp","type":"include"}]}

#ifndef LV2PLUG_UICONTROLLER_HPP
#define LV2PLUG_UICONTROLLER_HPP

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

namespace LV2Plug
	{
	class UIController
		{
		public:
			explicit UIController(LV2UI_Controller handle,LV2UI_Write_Function write_callback) noexcept:
				m_handle(handle),m_write_callback(write_callback)
				{}

			void write(float value,unsigned int port_id) noexcept
				{m_write_callback(m_handle,port_id,sizeof(value),0,&value);}

		private:
			LV2UI_Controller m_handle;
			LV2UI_Write_Function m_write_callback;
		};
	}

#endif
