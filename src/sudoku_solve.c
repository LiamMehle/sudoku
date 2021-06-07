#include "sudoku_solve.h"
#include "utils.h"
#include "types.h"
#include "sudoku_validity_check.h"
#include <string.h>
/* If grid is filled, function moves to another grid */
static
void _solve_sudoku(int row, int column);

static Board sudoku;

/**
 * @brief 
 */
static
void move(int row, int column)
{
	if (column < 8)
		_solve_sudoku(row, column + 1);
	else
		_solve_sudoku(row + 1, 0);
}

/**
 * @brief board-solving internal function
 * 
 */
// _solve_sudoku and move are to be considered one unit
static
void _solve_sudoku(int row, int column) {
/* If row > 8, then Sudoku is solved */
	if (row > 8) {
		return;
	}
/* If in given grid there is already a number different from 0, we move */
	if (sudoku[at(column,row)] != 0) {
		move(row, column);
/* If there is 0, it is filled with number and then move */
	} else {
		int licznik;
		for (licznik = 1; licznik <= 9; licznik++) {
			if ((check_row(sudoku, row, licznik) == 0) && (check_column(sudoku, column, licznik) == 0) && (check_grid(sudoku, row, column, licznik) == 0)) {
				sudoku[at(column,row)] = licznik;
				move(row, column);
			}
		}
		//sudoku[at(column,row)] = 0;
	}
	return;
}

/**
 * @brief return solved board
 * Solves board using board solving internal funcitons.
 * @param board input board
 * @return solved board
 */

void solve_sudoku(Board board) {
	memcpy(sudoku, board, sizeof(Board));
	_solve_sudoku(0, 0);
	memcpy(board, sudoku, sizeof(Board));
}