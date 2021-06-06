#include "game.h"
#include "utils.h"
#include "types.h"
#include "screen_ops.h"
#include "frame_buffer_ops.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "sudoku_validity_check.h"

enum input {
	input_clear = 0,
	input_failed_input = 1,
	input_invalid,
	input_given_overwrite,
	input_quit,
	input_row_invalid,
	input_col_invalid,
	input_grid_invalid,
	input_print_original
};

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
			return input_quit;
		if(x == 'o' || x == 'O')
			return input_print_original;
		if(isalnum(x))
			return -1;
	}
	while(1) {
		y = getchar();
		if((y >= 'A' && y <= 'I') || (y >= 'a' && y <= 'i'))
			break;
		if(isalnum(y))
			return input_invalid;
	}
	while(1) {
		digit = getchar();
		if(digit >= '0' && digit <= '9')
			break;
		if(isalpha(digit))
			return input_invalid;
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

/**
 * @brief zažene in izvaja logiko igre
 * zažene in izvaja logiko igre
 * @param Settings nastavitve, ki igre
 * 
 */
void start_game([[maybe_unused]]const Settings settings) {

	const Board original_board = { 9,0,0,2,3,7,6,8,0,
	                               0,2,0,8,4,0,0,7,3,
	                               8,0,7,1,0,5,0,2,9,
	                               0,0,4,5,9,8,3,0,0,
	                               2,0,0,0,0,1,0,0,6,
	                               5,1,0,0,0,0,0,4,7,
	                               4,0,1,3,0,6,2,9,5,
	                               0,5,0,9,1,0,7,3,8,
	                               3,0,8,0,5,0,0,0,0 };

	Board active_board;
	memcpy(active_board, original_board, sizeof(Board));

	FrameBuffer fb = make_framebuffer();
	board_to_framebuffer(active_board, fb);
	const FrameBuffer original_fb = framebuffer_clone(fb);;

	char input_flag = input_clear;

	while(1) {
		// output
		clear_screen();
		if(input_flag == input_print_original) {
			print_frame_buffer(original_fb);
			input_flag = input_clear;
		}

		print_frame_buffer(fb); // <---------

		if(input_flag == input_invalid)
			input_flag = input_failed_input;

		switch(input_flag) {
			case input_failed_input:
				puts("Invalid input!");
				break;

			case input_quit:
				return;

			case input_given_overwrite:
				puts("It's a given.");
				break;

			case input_row_invalid:
				puts("Invalid row.");
				break;

			case input_col_invalid:
				puts("Invalid collum.");
				break;

			case input_grid_invalid:
				puts("Invalid grid.");
				break;

			case input_clear:
				break;

			default:
				printf("error=%d\n", input_flag);
		}
		input_flag = input_clear;

		// input
		short x, y, digit;
		input_flag = get_game_input(&x, &y, &digit);
		if(input_flag)       // state has been set by get_game_input()
			continue;
		// check input
		if(x < 0 || x > 9
		|| y < 0 || x > 9
		|| digit < 0 || digit > 9) {
			input_flag = input_invalid;
		}

		// check if it's a given
		if(original_board[at(x,y)] != 0) {
			input_flag = input_given_overwrite;
			continue;
		}

		if(check_row(active_board, y, digit)) {
			input_flag = input_row_invalid;
			continue;
		}
		if(check_collum(active_board, x, digit)) {
			input_flag = input_col_invalid;
			continue;
		}
		if(check_grid(active_board, y, x, digit)) {
			input_flag = input_grid_invalid;
			continue;
		}

		// input is (assumed to be) valid
		active_board[at(x, y)] = digit;    // update board
		// updating the framebuffer directly with the change is faster than
		// redrawing the entire buffer
		fb.data[fb_at(x,y)] = digit != 0 ? digit+'0' : '_';
	}
}

