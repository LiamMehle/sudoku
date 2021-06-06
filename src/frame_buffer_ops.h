//#pragma once
#include "types.h"
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "utils.h"

#define width            21
#define height           10
#define framebuffer_size (width*height)

FrameBuffer make_framebuffer();
void print_board(uint8_t* board);
int print_frame_buffer(FrameBuffer fb);
void framebuffer_to_board(FrameBuffer fb, Board* board);
void board_to_framebuffer(Board board, FrameBuffer fb);
FrameBuffer framebuffer_clone(const FrameBuffer src);

 // supress warnings
static
char test0() {
	assert(make_framebuffer().data[fb_at(0,0)] == '_');
	assert(make_framebuffer().data[fb_at(1,0)] == '_');
	assert(make_framebuffer().data[fb_at(0,1)] == '_');
	assert(make_framebuffer().data[fb_at(2,2)] == '_');
	assert(make_framebuffer().data[fb_at(5,5)] == '_');
	return 0;
}