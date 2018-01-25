#pragma once

#include "Event.h"
#include <stdlib.h>

struct QuitEvent : Event {
	void StartEvent() override {}
	void Execute() override {
		exit(EXIT_SUCCESS);
	}
};