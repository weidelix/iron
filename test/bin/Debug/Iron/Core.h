#pragma once 

#define BIT(x) (1 << x)

#ifdef IRON_PLATFORM_WINDOW
    #ifdef IRON_BUILD_DLL
        #define IRON_API __declspec(dllexport)
    #else
        #define IRON_API __declspec(dllimport)
    #endif
#else
    #error Iron only supports window at the moment!
#endif

#ifdef ENABLE_ASSERT
    #define IRON_CORE_ASSERT(x,...) { if(!(x)) { IRON_CORE_C_ERROR(__VA_ARGS__); __debugbreak(); } }
    #define IRON_ASSERT(x,...) { if(!(x)) { LOG_C_ERROR(__VA_ARGS__); __debugbreak(); } }
#else
    #define IRON_CORE_ASSERT(x,...)
    #define IRON_ASSERT(x,...)
#endif


