#pragma once

#include "Event.h"
#include <string>
#include <iostream>
struct PrintEvent : Event {
	std::string msg;
	PrintEvent(std::string& s) : msg(s) {}
	PrintEvent(const char s[]) : msg(s) {}

	void StartEvent() override {}
	void Execute() override {
		std::cout << msg << std::endl;
	}
};