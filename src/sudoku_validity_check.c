#include "sudoku_validity_check.h"


/**
 * @brief preveri validnost v vrstici
 * Preveri ali število se pojavi v isti vrstici enkrat ali več
 * @param sudoku Board tip, ki zapisuje stanje igre ob vnosu vrednosti
 * @param row indeks vrstice, v katero spada število
 * @param liczba število za vpisati v vrstico
 * @return 0, če se število ne pojavi v vrstici, ne-0 če se.
 */
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

/**
 * @brief preveri validnost v stolpcu
 * Preveri ali število se pojavi v istem stolpcu enkrat ali več
 * @param sudoku Board tip, ki zapisuje stanje igre ob vnosu vrednosti
 * @param row indeks stolpca, v katero spada število
 * @param liczba število za vpisati v stolpec
 * @return 0, če se število ne pojavi v stolpcu, ne-0 če se.
 */
/* Function checks, if in given column the number already exists */
int check_column(Board sudoku, int column, int liczba)
{
    int row;
    for (row = 0; row < 9; row++)
    {
        if (sudoku[at(row,column)] == liczba)
            return 1;
    }
    return 0;
}

/**
 * @brief preveri validnost v oknu
 * Preveri ali število se pojavi v istem oknu enkrat ali več
 * @param sudoku Board tip, ki zapisuje stanje igre ob vnosu vrednosti
 * @param column x koordinata celice, v katerem bo vpisano število
 * @param row y koordinata celice, v katerem bo vpisano število
 * @param liczba število za vpisati v celico
 * @return 0, če se število ne pojavi v vrstici, ne-0 če se.
 */
/* Function checks, if in given grid the number already exists */
int check_grid(Board sudoku, int column, int row, int liczba)
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