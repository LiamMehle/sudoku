#pragma once

#ifdef __GNUC__ // works on clang and gcc
	#define prefetch(x) __builtin_prefetch(x)
#else
	#define prefetch(x)
#endif
