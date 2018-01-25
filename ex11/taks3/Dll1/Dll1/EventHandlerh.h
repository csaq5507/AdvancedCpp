#pragma once
#ifdef  __PLUGIN__CONTROLL_API
#define _API_EVENT __declspec(dllimport)
#else
#define _API_EVENT __declspec(dllexport)
#endif

#include "Event.h"
#include <map>
#include <memory>

class EventHandler {
	public:
		static _API_EVENT int AddEvent(std::shared_ptr<Event> e);

		static _API_EVENT std::shared_ptr<Event> GetEvent(int id);

		static _API_EVENT bool RemoveEvent(int id);

		static _API_EVENT void DisableEvent(int id);

		static _API_EVENT void ActivateEvent(int id);
};