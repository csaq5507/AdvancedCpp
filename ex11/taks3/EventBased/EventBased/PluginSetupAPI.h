#pragma once
#ifdef  __PLUGIN__
#define _API_PLUG __declspec(dllexport)
#else
#define _API_PLUG __declspec(dllimport)
#endif


_API_PLUG bool InitializePlugin();
_API_PLUG bool DeinitializePlugin();

//After each iteration of the event loop the Change()
//function of each plugin is called
_API_PLUG void Change(int round);