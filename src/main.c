
/*
 * 
 * Pri pisanju kode smo imeli v mislih nadgradnjo samega
 * programa
 * (algoritem za reševanje, algoritem za generiranje, timer,
 *  itd.).
 * 
 */

//#include <stdio.h>
//#include <stdint.h>
#include <string.h>
#include "types.h"
#include "frame_buffer_ops.h"
#include <alloca.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "game.h"
#include "screen_ops.h"
#include "common.h"
#include "utils.h"

enum menu_options {
	menu_play = 1,
	menu_settings = 2,
	menu_tutorial = 3,
	menu_exit = 4
};

/**
 * @brief glavni meni
 * napiše glavni meni z funkcijo fwrite()
 */
static
inline
void show_main_menu() {
	const char menu[] =
	"----< main menu >----\n"
	"1: play\n"
	"2: settings\n"
	"3: tutorial\n"
	"4: exit\n"
	"----< ====[]=== >----\n";
	fwrite(menu, sizeof menu, 1, stdout);
}

/**
 * @brief vrne celo število od uporabnika
 * upraša po in vrne vrednost, ki je zahtevana (celo število)
 * @return celo število uporabnika
 */
static
inline
int get_int() {
	// write prompt
	fwrite(": ", 2, 1, stdout);
	fflush(stdout);

	// parse int
	char buffer[256];
	short buffer_index = 0;
	while(true) {
		buffer[buffer_index] = getchar();
		// is this the end of the number?
		if(buffer[buffer_index] == '\n' && buffer_index != 0) {
			buffer_index++;
			break;
		}
		// else is this garbage data?
		if(!isdigit(buffer[buffer_index])) {
			putchar('\b'); // delete last char
			continue;      // do not increment index
		}
		// probbably valid
		buffer_index++;
	}
	buffer[buffer_index] = '\0'; // null termination
	
	// translate digit out of it
	int ret;
	sscanf(buffer, "%d", &ret);
	return ret;
}

Settings settings_menu() {
	puts("This is a stub.");
	return 0;
}

/**
 * @brief glavni navodila
 * napiše glavni navodila z funkcijo fwrite()
 */
void show_tutorial() {
	const char text[] =
	"\n"
	"O/o - show original problem\n"
	"Q/q - quit\n"
	"S/s - solve (show solved) [BROKEN]\n"
	"xyv - example: ab3\n"
	"|||\n"
	"||`-value, 0 = empty\n"
	"|`--y coordinate\n"
	"`---X coordinate\n";
	fwrite(text, sizeof text, 1, stdout);
}
int main() {
	// testing purposes
	//test0();
	//start_game(0);
	//return 0;

	clear_screen();

	Settings settings = 0;
	while(true) {
		show_main_menu();
		const int selection = get_int();
		switch(selection) {
		case menu_play:
			start_game(settings);
			break;
		case menu_settings:
			settings = settings_menu();
			break;
		case menu_tutorial:
			show_tutorial();
			break;
		case menu_exit:
			return 0;
			break;
		}
	}
	return 1;
}

/*
	Board board;
	memset(board, 1, 9*9);
	print_board(board);
	FrameBuffer fb = make_framebuffer();
	board_to_framebuffer(board, fb);
	print_frame_buffer(fb);

	framebuffer_to_board(fb, &board);
	print_board(board);
*/