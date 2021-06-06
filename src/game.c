#include "game.h"
#include "types.h"
#include "screen_ops.h"
#include "frame_buffer_ops.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

char get_game_input(short* const x_out,
                    short* const y_out,
                    short* const digit_out) {
	// BC2
	fwrite(": ", 2, 1, stdout);
	fflush(stdout);
	fflush(stdin);
	char x, y, digit;
	while(1) {
		x = getchar();
		if((x >= 'A' && x <= 'I') || (x >= 'a' && x <= 'i'))
			break;
		// -------------- special case -------------------
		if(x == 'q' || x == 'Q')
			return 1;
		if(isalnum(x))
			return -1;
	}
	while(1) {
		y = getchar();
		if((y >= 'A' && y <= 'I') || (y >= 'a' && y <= 'i'))
			break;
		if(isalnum(y))
			return -2;
	}
	while(1) {
		digit = getchar();
		if(digit >= '0' && digit <= '9')
			break;
		if(isalpha(digit))
			return -3;
	}
	if(x >= 'a' && x <= 'i')
		x = x + 'A' - 'a';
	if(y >= 'a' && y <= 'i')
		y = y + 'A' - 'a';
	*x_out     = x - 'A';
	*y_out     = y - 'A';
	*digit_out = digit - '0';
	return 0;
}

/*
	todo:
	prevent givens from being modified
*/

void start_game([[maybe_unused]]const Settings settings) {

	Board board = { 9,0,0,2,3,7,6,8,0,
	                0,2,0,8,4,0,0,7,3,
	                8,0,7,1,0,5,0,2,9,
	                0,0,4,5,9,8,3,0,0,
	                2,0,0,0,0,1,0,0,6,
	                5,1,0,0,0,0,0,4,7,
	                4,0,1,3,0,6,2,9,5,
	                0,5,0,9,1,0,7,3,8,
	                3,0,8,0,5,0,0,0,0 };

	FrameBuffer fb = make_framebuffer();
	char dirty_input = 0;

	while(1) {
		// output
		board_to_framebuffer(board, fb);
		//clear_screen();
		print_frame_buffer(fb);
		if(dirty_input) {
			puts("Invalid input!");
			dirty_input = 0;
		}

		// input
		short x, y, digit;
		const char err = get_game_input(&x, &y, &digit);
		if(err == 1) // quit
			return;
		if(err) {
			dirty_input = 1;
			continue;
		}
		// check parameters
		if(x < 0 || x > 9
		|| y < 0 || x > 9
		|| digit < 0 || digit > 9) {
			dirty_input = 1;
		}
		board[at(x, y)] = digit;
	}
}

