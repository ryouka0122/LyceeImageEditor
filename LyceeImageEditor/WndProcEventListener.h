#ifndef __WNDPROC_EVENT_LISTENER__HEADER__
#define __WNDPROC_EVENT_LISTENER__HEADER__

#include "includes.h"
#include "Functor.h"

namespace lycee {

	typedef struct _tagWndProcParam {
		HWND hWnd;
		UINT uMsg;
		WPARAM wp;
		LPARAM lp;
	}WndProcParam;


	inline WndProcParam CreateWndProcParam(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam) {
		WndProcParam wpp = {_hWnd, _uMsg, _wParam, _lParam};
		return wpp;
	}

	class WndProcEventListener
	{
	public:
		explicit WndProcEventListener(HWND hWnd);
		virtual ~WndProcEventListener();


	public:
		typedef Functor<UINT, WndProcParam> WndProcEvent;

		void add(UINT uMsg, WndProcEvent wndProcEvent);
		void remove(UINT uMsg);
		void clear();

		LRESULT invoke(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		LRESULT invoke(WndProcParam param);

	private:
		HWND handle;
		std::map<UINT, WndProcEvent> eventList;

	};

}	// lycee
#endif	// __WNDPROC_EVENT_LISTENER__HEADER__