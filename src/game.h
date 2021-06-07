#pragma once
#include "types.h"
void start_game(const Settings settings);

enum settings {
	settings_empty_board,
	settings_preset_board,
	settings_custom_board
};