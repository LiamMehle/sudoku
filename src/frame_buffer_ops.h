//#pragma once
#include "types.h"
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

// returns offset into board
[[maybe_unused]] // supress warnings
static
short at(int x, int y) {
	return x + y*9;
}

static
short fb_at(const short x, const short y) {
	return (y+1)*21+(x+1)*2;
}

#define width            21
#define height           10
#define framebuffer_size (width*height)

FrameBuffer make_framebuffer();
void print_board(uint8_t* board);
int print_frame_buffer(FrameBuffer fb);
void framebuffer_to_board(FrameBuffer fb, Board* board);
void board_to_framebuffer(Board board, FrameBuffer fb);

[[maybe_unused]] // supress warnings
static
char test0() {
	assert(make_framebuffer().data[fb_at(0,0)] == '_');
	assert(make_framebuffer().data[fb_at(1,0)] == '_');
	assert(make_framebuffer().data[fb_at(0,1)] == '_');
	assert(make_framebuffer().data[fb_at(2,2)] == '_');
	assert(make_framebuffer().data[fb_at(5,5)] == '_');
	return 0;
}