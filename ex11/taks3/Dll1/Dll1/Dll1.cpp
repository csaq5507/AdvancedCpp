// Dll1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#define _API_PLUG __declspec(dllexport)
constexpr int DLL_FUNCTIONS_N = 5;
const char* MAIN_FUNCTION_NAMES[DLL_FUNCTIONS_N] = {
														"AddEvent",
														"GetEvent",
														"RemoveEvent",
														"DisableEvent",
														"ActivateEvent",
													};
namespace fs = std::experimental::filesystem;
using AddType = int(*)(std::shared_ptr<Event>);
using RemoveFunType = void(*)(int);
using ChangeStatusType = void(*)(int);
static int removeEventId;
static int swapEventId;
static HINSTANCE hGetProcIDDLL;

extern "C"
{
	_API_PLUG bool InitializePlugin() {
		std::cout << "called init " << std::endl;
		//for debugging
		hGetProcIDDLL = GetModuleHandle(nullptr);
		if (!hGetProcIDDLL) {
			std::cout << "could not load module" << std::endl;
			exit(EXIT_FAILURE);
		}
		AddType fun = (AddType)GetProcAddress(hGetProcIDDLL, "AddEvent");
		if (!fun) {
			std::cout << "could not laod function " << "AddEvent" << " of plugin " << std::endl;
			exit(EXIT_FAILURE);
		}
		removeEventId = fun(std::shared_ptr<Event>(new PrintEvent("I will be removed at the 4 round")));
		swapEventId = fun(std::shared_ptr<Event>(new PrintEvent("I will stay each even round")));
		return true;
	}

	_API_PLUG bool DeinitializePlugin() {
		std::cout << "called end " << std::endl;
		return true;
	}

	//After each iteration of the event loop the Change()
	//function of each plugin is called
	_API_PLUG void Change(int round) {
		ChangeStatusType dis = (ChangeStatusType)GetProcAddress(hGetProcIDDLL, "DisableEvent");
		ChangeStatusType act = (ChangeStatusType)GetProcAddress(hGetProcIDDLL, "ActivateEvent");
		if (round >= 4) {
			RemoveFunType rem = (RemoveFunType)GetProcAddress(hGetProcIDDLL, "RemoveEvent");
			rem(removeEventId);
		}
		round = (round + 1) % 2;
		round != 0 ? dis(swapEventId) : act(swapEventId);
	}
}