//#pragma once
#include "types.h"
#include <stdint.h>
#include <stddef.h>

// returns offset into board
inline
short at(int x, int y) {
	return x + y*9;
}

#define width            21
#define height           10
#define framebuffer_size (width*height)

FrameBuffer make_framebuffer();
void print_board(uint8_t* board);
int print_frame_buffer(FrameBuffer fb);
void framebuffer_to_board(FrameBuffer fb, Board* board);
void board_to_framebuffer(Board board, FrameBuffer fb);