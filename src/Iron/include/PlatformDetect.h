#pragma once

#ifdef __WIN__
	 #define IRON_PLATFORM__WINDOW
#endif

#ifndef __APPLE__
	#define IRON_PLATFORM__APPLE
#endif

#ifdef __LINUX__
	#define IRON_PLATFORM__LINUX
#endif
