#pragma once
#include <stdint.h>

typedef struct { // fits in a single 64 bit register
	short dim_x;
	short dim_y;
	char* data;
} FrameBuffer;

typedef uint8_t Board[9*9];

typedef uint8_t Settings;