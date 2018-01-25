#include "EventHandler.h"
#include "ExecutableEvent.h"
#include <map>
#include <memory>



extern "C"
{
	int AddEvent(std::shared_ptr<Event> e) {
		ExecutableEvent handle{ e };
		int id = handle.GetId();
		EventHandler::eventMap.emplace(id, std::move(handle));
		return id;
	}

	std::shared_ptr<Event> GetEvent(int id) {
		auto pos = EventHandler::eventMap.find(id);
		if (pos != EventHandler::eventMap.end()) {
			return (*pos).second.GetEvent();
		}
		return nullptr;
	}

	bool RemoveEvent(int id) {
		auto pos = EventHandler::eventMap.find(id);
		if (pos != EventHandler::eventMap.end()) {
			EventHandler::eventMap.erase(id);
			return true;
		}
		return false;
	}

	void DisableEvent(int id) {
		auto pos = EventHandler::eventMap.find(id);
		if (pos != EventHandler::eventMap.end()) {
			(*pos).second.Disable();
		}
	}

	void ActivateEvent(int id) {
		auto pos = EventHandler::eventMap.find(id);
		if (pos != EventHandler::eventMap.end()) {
			(*pos).second.Activate();
		}
	}
}

std::map<int, ExecutableEvent> EventHandler::eventMap{};