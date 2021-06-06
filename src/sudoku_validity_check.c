#include "sudoku_validity_check.h"

/* Function checks, if in given row the number already exists */
int check_row(Board sudoku, int row, int liczba)
{
    int column;
    for (column = 0; column < 9; column++)
    {
        if (sudoku[at(row,column)] == liczba)
            return 1;
    }
    return 0;
}

/* Function checks, if in given column the number already exists */
int check_collum(Board sudoku, int column, int liczba)
{
    int row;
    for (row = 0; row < 9; row++)
    {
        if (sudoku[at(row,column)] == liczba)
            return 1;
    }
    return 0;
}

/* Function checks, if in given grid the number already exists */
int check_grid(Board sudoku, int row, int column, int liczba)
{
    row = (row/3)*3;
    column = (column/3)*3;
    int i;
    int j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (sudoku[at(row + i,column + j)] == liczba)
                return 1;
        }
    }
    return 0;
}