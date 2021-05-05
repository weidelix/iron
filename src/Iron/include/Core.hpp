#pragma once 

#define BIT(x) (1 << x)

#if defined(IRON_PLATFORM_WINDOW)
		#if defined(IRON_BUILD_DLL)
		  	#if defined(USE_CLANG)       // Set Clang specific macros
				#define IRON_API __declspec(dllexport)
			#endif
			#if defined(USE_MSVC)        // Set MSVC specific macros
				#define IRON_API __declspec(dllexport)
			#endif
		#else
			#if defined(USE_CLANG)
				#define IRON_API __declspec(dllimport)
			#endif
			#if defined(USE_MSVC)
				#define IRON_API __declspec(dllimport)
			#endif
	 #endif
#elif defined(IRON_PLATFORM_LINUX)
		#if defined(IRON_BUILD_DLL)
		  	#define IRON_API __attribute__((visibility("default")))
		#else
			#define IRON_API
		#endif
#else
	#error Iron only supports window at the moment!
#endif

#if defined(ENABLE_ASSERT)
	#if defined(IRON_PLATFORM_LINUX)
		#define IRON_CORE_ASSERT(x,...) { if(!(x)) { IRON_CORE_ERROR(__VA_ARGS__); } }
		#define IRON_ASSERT(x,...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); } }
	#else
		#define IRON_CORE_ASSERT(x,...) { if(!(x)) { IRON_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
		#define IRON_ASSERT(x,...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); __debugbreak(); } }
	#endif
#else
	#define IRON_CORE_ASSERT(x,...)
	#define IRON_ASSERT(x,...)
#endif