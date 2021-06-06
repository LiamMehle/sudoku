#pragma once

#ifdef __GNUC__ // works on clang and gcc
	#define prefetch(x) __builtin_prefetch(x)
#else
	#define prefetch(x)
#endif

#define number_to_letter(x) (x+'A')
#define letter_to_number(x) (x-'A')
