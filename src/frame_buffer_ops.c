#include "frame_buffer_ops.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
/*
empty frame buffer
  A B C D E F G H I
A|_|_|_|_|_|_|_|_|_|
B|_|_|_|_|_|_|_|_|_|
C|_|_|_|_|_|_|_|_|_|
D|_|_|_|_|_|_|_|_|_|
E|_|_|_|_|_|_|_|_|_|
F|_|_|_|_|_|_|_|_|_|
G|_|_|_|_|_|_|_|_|_|
H|_|_|_|_|_|_|_|_|_|
I|_|_|_|_|_|_|_|_|_|

*/

short board_at(const short x, const short y) {
	return y*21+x;
}

FrameBuffer make_framebuffer() {
	FrameBuffer ret = {
		.dim_x = width,
		.dim_y = height,
		.data  = (char*) malloc(framebuffer_size),
	};
	size_t pointer = 0; // offset into the buffer to write to

#define WRITE(x) ret.data[pointer++] = x;

	WRITE(' ');
	for(int x = 0; x < 9; x++) {
		WRITE(' ');
		WRITE('A'+x);
	}
	WRITE('\n');

	for(int y = 0; y < 9; y++) {
		WRITE('A'+y);
		WRITE('|');
		for(int x = 0; x < 9; x++) {
			WRITE('_');
			WRITE('|');
		}
		WRITE('\n');
	}

//#undef WRITE
//#define WRITE_AT(A, X, Y) ret.data[board_at(X, Y)] = A
//
//	for(int y = 0; y < 3; y++) {       // y = 1
//		for(int x = 0; x < 3; x++) {     // x = 0
//			const short square_x = x*1+1;  //   = 1
//			const short square_y = y*3+0;  //   = 3
//			const short square_x_left  = square_x;   // = 1
//			const short square_y_top   = square_y;
//			const short square_x_right = square_x+4; // = 5
//			const short square_y_bot   = square_y+4;
//
//			// top
//			for(int x_inner = square_x_left; x_inner <= square_x_right; x_inner++)
//				WRITE_AT('#', x_inner, square_y_top);
//			// bottom
//			for(int x_inner = square_x_left; x_inner < square_x_right; x_inner++)
//				WRITE_AT('#', x_inner, square_y_bot);
//			// left
//			for(int y_inner = square_y_top; y_inner < square_y_bot; y_inner++)
//				WRITE_AT('#', square_x_left, y_inner);
//			// right
//			for(int y_inner = square_y_top; y_inner < square_y_bot; y_inner++)
//				WRITE_AT('#', square_x_right, y_inner);
//		}
//	}
//
//#undef WRITE_AT

	return ret;
}

void print_board(uint8_t* board) {
	for(int x = 0; x < 9*2+1; x++)
		putchar('_');
	putchar('\n');

	for(int x = 0; x < 9; x++) {
		putchar('|');
		for(int y = 0; y < 9; y++) {
			const uint8_t cell = board[at(x, y)];
			if(cell == 0)
				printf("_|");
			else
				printf("%u|", cell);
		}
		putchar('\n');
	}
}

int print_frame_buffer(const FrameBuffer fb) {
	return fwrite(fb.data, fb.dim_x, fb.dim_y, stdout);
}

void framebuffer_to_board(const FrameBuffer fb, Board* board) {
	int board_index = 0;
	for(int i = 0; i < framebuffer_size; i++) {
		const char c = fb.data[i];
		if(isdigit(c)) {
			(*board)[board_index++] = c - '0';
			//printf("%c => %d", c, c - '0');
			continue;
		}
		if(c == '_') {
			(*board)[board_index++] = 0;
			//printf("%c => %d", c, 0);
			continue;
		}
		//printf("%c is not a number\n", c);
		// all other characters to be ignored
	}
}

void board_to_framebuffer(Board board, FrameBuffer fb) {
	for(int y = 0; y < 9; y++) {
		for(int x = 0; x < 9; x++) {
			const int digit = board[at(x,y)];
			const int frame_y = 1 + y;
			const int frame_x = 1 + x*2;
			const int offset = frame_y*21+frame_x;
			//printf("x: %d y: %d off: %d\n", frame_x, frame_y, offset);
			//print_frame_buffer(fb);
			if(digit == 0)
				fb.data[offset] = '_';
			else
				fb.data[offset] = digit + '0';
		}
	}
}