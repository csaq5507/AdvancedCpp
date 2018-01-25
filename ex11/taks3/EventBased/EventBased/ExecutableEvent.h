#pragma once
#include "Event.h"
#include <memory>

class ExecutableEvent {
	bool run = true;
	static int id;
	int eventId;
	std::shared_ptr<Event> eventPtr;
public:
	ExecutableEvent(std::shared_ptr<Event> e) : eventId{ id }, eventPtr{ e } { id++; }
	ExecutableEvent(ExecutableEvent&& other) : eventId{ other.eventId }, eventPtr{ other.eventPtr } {}

	std::shared_ptr<Event> GetEvent() const {return eventPtr;}

	int GetId() { return eventId; }
	void Activate() {run = true;}
	void Disable() {run = false;}
	void Execute() {if(run)	eventPtr->Execute();}
};