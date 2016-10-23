//@ {"targets":[{"name":"uinotifier.hpp","type":"include"}]}

#ifndef LV2PLUG_UINOTIFIER_HPP
#define LV2PLUG_UINOTIFIER_HPP

#include "visibility.hpp"
#include "plugin_ui.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <type_traits>

namespace LV2Plug
	{
	template<class ClientUI>
	using UICallback = void(*)(ClientUI&,const void* data);

	template<class T>
	std::enable_if_t<std::is_pointer<T>::value,const std::remove_pointer_t<T>*> valueGet(const void* value) noexcept
		{return reinterpret_cast<const std::remove_pointer_t<T>* >(value);}

	template<class T>
	std::enable_if_t<!std::is_pointer<T>::value,T> valueGet(const void* value) noexcept
		{return *reinterpret_cast<const T*>(value);}

	template<class ClientUI,unsigned int PortNumber>
	void process(ClientUI& ui,const void* data)
		{
		update<PortNumber>(ui,valueGet< PortType<PortNumber,ClientUI> >(data));
		}

	template<class T,unsigned int N>
	struct Array
		{
		static constexpr unsigned int size() noexcept
			{return N;}
		T m_data[N];
		};

	template<class ClientUI>
	class UINotifier
		{
		public:
			static constexpr void call(ClientUI& ui,unsigned int k,const void* data)
				{
				if(k<s_ui_callbacks.size())
					{return (*s_ui_callbacks.m_data[k])(ui,data);}
				}

			static constexpr unsigned int portCountGet() noexcept
				{
				return ClientUI::descriptor().portCount();
				}

		private:
			static constexpr unsigned int PORT_COUNT=portCountGet();

			template<unsigned int N=0,int dummy=0>
			struct UICallbacksElement:public UICallbacksElement<N+1,dummy>
				{static constexpr auto element=process<ClientUI,N>;};
			template<int dummy>
			struct UICallbacksElement<PORT_COUNT,dummy>
				{};

			template<class Callback>
			static constexpr void uiCallbacksEnum(Callback&& cb)
				{uiCallbacksEnumImpl(cb);}

			template<unsigned int index>
			static constexpr UICallback<ClientUI> uiCallbacksGet()
				{return UICallbacksElement<index>::element;}

			template<unsigned int index=0,class Callback>
			static constexpr std::enable_if_t<index!=PORT_COUNT,void>
			uiCallbacksEnumImpl(Callback& cb)
				{
				cb(index,uiCallbacksGet<index>());
				uiCallbacksEnumImpl<index+1,Callback>(cb);
				}

			template<unsigned int index=0,class Callback>
			static constexpr std::enable_if_t<index==PORT_COUNT,void>
			uiCallbacksEnumImpl(Callback& cb)
				{}

			struct UICallbackSet
				{
				constexpr void operator()(size_t k,UICallback<ClientUI> notifier)
					{ret.m_data[k]=notifier;}
				Array<UICallback<ClientUI>,PORT_COUNT>& ret;
				};
			static constexpr auto uiCallbacksCollect()
				{
				Array<UICallback<ClientUI>,PORT_COUNT> ret{};
				uiCallbacksEnum(UICallbackSet{ret});
				return ret;
				}
			static constexpr const Array<UICallback<ClientUI>,PORT_COUNT> s_ui_callbacks=
				uiCallbacksCollect();
		};

	template<class ClientUI>
	constexpr const Array<UICallback<ClientUI>,UINotifier<ClientUI>::PORT_COUNT> UINotifier<ClientUI>::s_ui_callbacks;
	}

#endif
