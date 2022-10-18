#pragma once

#ifdef WI_DEBUG
	#ifdef WI_PLATFORM_WIN
		#define WI_DEBUGBREAK() __debugbreak()
	#else
		#error "Only windows support"
	#endif
#else
	#define WI_DEBUGBREAK()
#endif