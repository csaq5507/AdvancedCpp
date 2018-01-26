#include "Event.h"
#include "PrintEvent.h"
#include "QuitEvent.h"
#include "EventHandler.h"
#include <vector>
#include <memory>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <experimental\filesystem>
#else
#include "experimental/filesystem"
#include <dlfcn.h>
#endif


using Base = bool(*)();
using Change = bool(*)(int);
constexpr int DLL_FUNCTIONS_N = 3;
const char* DLL_FUNCTION_NAMES[DLL_FUNCTIONS_N] =	{
														"InitializePlugin",
														"DeinitializePlugin",
														"Change",
													};
namespace fs = std::experimental::filesystem;

# ifdef _WIN32
template <typename T, typename Con>
void InsertFunc(Con& container, HINSTANCE inst, const char* name) {
	T fun = (T)GetProcAddress(inst, name);
	if (!fun) {
		std::cout << "could not laod function " << name << " of plugin " << std::endl;
		exit(EXIT_FAILURE);
	}
	container.push_back(fun);
}
#else
template <typename T, typename Con>
void InsertFunc(Con& container, void* inst, const char* name) {
	T fun = (T)::dlsym(inst, name);

	if (!fun) {
		std::cout << "could not laod function " << name << " of plugin " << std::endl;
		exit(EXIT_FAILURE);
	}
	container.push_back(fun);
}
#endif

int main(void) {
	//create DLL
	//after compiling DLL and coping to dir
	//try execute init and del (only calls std::cout)
	fs::path pluginDir = fs::path(".") / "Plugin";
	std::vector<Base> initializeFunctionVec;
	std::vector<Change> changeFunctionVec;
	std::vector<Base> deinitializeFunctionVec;

	for (auto& p : fs::directory_iterator(pluginDir)) {
		std::string path = p.path().string();
		# ifdef _WIN32
			HINSTANCE hGetProcIDDLL = LoadLibrary(path.c_str());
			if (!hGetProcIDDLL) {
				std::cout << "could not laod plugin " << p << std::endl;
				exit(EXIT_FAILURE);
			}

			InsertFunc<Base>(initializeFunctionVec, hGetProcIDDLL, "InitializePlugin");
			InsertFunc<Base>(deinitializeFunctionVec, hGetProcIDDLL, "DeinitializePlugin");
			InsertFunc<Change>(changeFunctionVec, hGetProcIDDLL, "Change");
		# else
			void *hGetProcIDDLL = ::dlopen(path.c_str(), RTLD_LAZY);
			if (!hGetProcIDDLL) {
				std::cout << "could not laod plugin " << p << std::endl;
				exit(EXIT_FAILURE);
			}
			InsertFunc<Base>(initializeFunctionVec, hGetProcIDDLL, "InitializePlugin");
			InsertFunc<Base>(deinitializeFunctionVec, hGetProcIDDLL, "DeinitializePlugin");
			InsertFunc<Change>(changeFunctionVec, hGetProcIDDLL, "Change");
		# endif

	}
	for (auto fun : initializeFunctionVec) {
		fun();
	}

	AddEvent(std::shared_ptr<Event>(new PrintEvent("Test not plugin event")));
	
	int i = 0;
	while (true) {
		for (auto i = EventHandler::Begin(); i != EventHandler::End(); i++) {
			(*i).second.Execute();
		}
		for (auto p : changeFunctionVec) {
			p(i);
		}
		i++;
	}
}