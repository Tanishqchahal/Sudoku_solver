// Code: Here include your necessary library (s)
#include <stdio.h>
#include <stdbool.h>

// Code: Write your global variables here, like : 
#define N 9


void print(int grid[N][N])
{
    for (int row = 1; row<=N; row++)
    {
        for (int col = 1; col<=N; col++)
        {   
            if (grid[row-1][col-1] == 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", grid[row-1][col-1]);
            }    
            if (col%3 == 0)
            {
                printf("| ");
            }    
        }
        printf("\n");
        if (row%3 == 0)
        {
            printf("------+-------+--------\n");
        }
    }
}   

void findEmptyCell(int grid[N][N], int emptyCell[2])
{   
    emptyCell[0] = -1;
    emptyCell[1] = -1;
    for (int row = 0; row<N; row++)
    {
        for (int col = 0; col<N; col++)
        {
            if (grid[row][col] == 0)
            {
                emptyCell[0] = row;
                emptyCell[1] = col;
                return;
               
            }
        }
    }
}

bool validInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col<N; col++)
    {
        if (grid[row][col] == num)
        {
            return false;
        }
    }
    return true;
}

bool validInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row<N; row++)
    {
        if (grid[row][col] == num)
        {
            return false;
        }
    }
    return true;
}

bool validInSquare(int grid[N][N], int row, int col, int num)
{
    int rowStart = (row / 3)*3;
    int colStart = (col / 3)*3;
    for (int row = rowStart; row<rowStart+3; row++)
    {
        for (int col = colStart; col<colStart+3; col++)
        {
            if (grid[row][col] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool isValid(int grid[N][N], int row, int col, int num)
{
    return validInRow(grid, row, num) && validInCol(grid, col, num) && validInSquare(grid, row, col, num);
}

bool solveSudoku(int grid[N][N]) 
{
// Code: count+1, the number of times the function was called. 
// Code: here write the implementation of solveSudoku
    int count = count + 1;
    int emptyCell[2];
    findEmptyCell(grid, emptyCell);
    int emptyCellRow = emptyCell[0];
    int emptyCellCol = emptyCell[1];
    if (emptyCellRow == -1)
    {
        printf ("Solution found after %d iterations: \n\n" , count );   
        return true;
    }
    else
    {
        for(int guess=1; guess<10;guess++){
            if (isValid(grid, emptyCellRow, emptyCellCol, guess))
            {
                grid[emptyCellRow][emptyCellCol] = guess;
                if (solveSudoku(grid))
                {
                    return true;
                }
                grid[emptyCellRow][emptyCellCol] = 0;
            }
        }
    }
    return false;
}

int main ()
{
    // This is hard coding to receive the "grid"
    int grid [N][N] = {
    {0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 6, 0, 0, 0, 0, 3},
    {0, 7, 4, 0, 8, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 3, 0, 0, 2},
    {0, 8, 0, 0, 4, 0, 0, 1, 0}, 
    {6, 0, 0, 5, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 1, 0, 7, 8, 0}, 
    {5, 0, 0, 0, 0, 9, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 4, 0}};

    printf ("The input Sudoku puzzle : \n\n") ; 
    // "print" is a function we define to print the "grid" 
    print (grid) ;

    if (solveSudoku(grid))
    {
        // If the puzzle is solved then:
        // printf (" Solution found after %d iterations : \n" , count ); 
        print (grid ) ;
    }
    else 
    {
        printf ("No solution exists. \n" ) ;
    }

    return 0;
}