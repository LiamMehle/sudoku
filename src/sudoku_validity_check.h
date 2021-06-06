#pragma once
#include "types.h"
#include "utils.h"
/* Function checks, if in given row the number already exists */
int check_row(Board sudoku, int row, int liczba);

/* Function checks, if in given column the number already exists */
int check_collum(Board sudoku, int column, int liczba);

/* Function checks, if in given grid the number already exists */
int check_grid(Board sudoku, int row, int column, int liczba);
