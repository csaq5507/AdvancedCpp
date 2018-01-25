#pragma once
#ifdef  __PLUGIN__CONTROLL_API
#define _API_EVENT __declspec(dllimport)
#else
#define _API_EVENT __declspec(dllexport)
#endif

#include "ExecutableEvent.h"
#include <map>
#include <memory>

extern "C"
{
	//this funciton will be exported
	_API_EVENT int AddEvent(std::shared_ptr<Event> e);

	_API_EVENT std::shared_ptr<Event> GetEvent(int id);

	_API_EVENT bool RemoveEvent(int id);

	_API_EVENT void DisableEvent(int id);

	_API_EVENT void ActivateEvent(int id);
}


struct EventHandler {
	static std::map<int, ExecutableEvent> eventMap;

	// not exported
	static auto Begin() {
		return eventMap.begin();
	}
	static auto End() {
		return eventMap.end();
	}
};
