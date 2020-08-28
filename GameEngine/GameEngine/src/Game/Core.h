#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_ALL
		#define GE_API __declspec(dllexport)
	#else
		#define GE_API __declspec(dllimport)
	#endif
#else
	#error GameEngine only support Windows !
#endif