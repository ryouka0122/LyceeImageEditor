#include "WndProcEventListener.h"



lycee::WndProcEventListener::WndProcEventListener(HWND hWnd)
	: handle(hWnd)
{
	clear();
}


lycee::WndProcEventListener::~WndProcEventListener()
{
	clear();
}

void lycee::WndProcEventListener::add(UINT uMsg, WndProcEvent wndProcEvent)
{
	this->eventList[uMsg] = wndProcEvent;
}

void lycee::WndProcEventListener::remove(UINT uMsg)
{
	this->eventList.erase(uMsg);
}

void lycee::WndProcEventListener::clear()
{
	this->eventList.clear();
}

LRESULT lycee::WndProcEventListener::invoke(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee::WndProcParam param = { hWnd, uMsg, wp, lp };
	return invoke(param);
}

LRESULT lycee::WndProcEventListener::invoke(WndProcParam param)
{
	if (this->handle == param.hWnd) {
		std::map<UINT, lycee::WndProcEventListener::WndProcEvent>::iterator
			iter = this->eventList.find(param.uMsg);
		if (iter != this->eventList.end()) {
			return iter->second.invoke(param);
		}
	}
	return DefWindowProc(param.hWnd, param.uMsg, param.wp, param.lp);
}
