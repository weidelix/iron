#pragma once 

#ifdef IRON_PLATFORM_WINDOW
    #ifdef IRON_BUILD_DLL
        #define IRON_API __declspec(dllexport)
    #else
        #define IRON_API __declspec(dllimport)
    #endif
#else
    #error Iron only supports window at the moment!
#endif