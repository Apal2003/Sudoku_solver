/* Sudoku Solver */
#include<stdio.h>  // Include the standard I/O library for input and output

// Define a 9x9 puzzle array, initialized with the given Sudoku puzzle
int puzzel[9][9] = 
{
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0},
};

// Function declarations
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main()
{
    // Print the welcome message
    printf("\n\tWelcome to SUDOKU SOLVER !!!");
    printf("\n\nOriginal Puzzle: ");
    
    // Print the original puzzle
    print_puzzle(puzzel);
    
    // Call the solver function to solve the puzzle, starting from (0,0)
    if(solve_puzzle(puzzel, 0, 0))
    {
        // If solved, print the solved puzzle
        printf("\n The puzzle is solved: ");
        print_puzzle(puzzel);
    }
    else
    {
        // If not solvable, print a message
        printf("\n The puzzle is not solvable:\n");
    }
    return 0; // End of the program
}

// Function to solve the puzzle using recursion and backtracking
int solve_puzzle(int puzzle[9][9], int row, int col)
{
    // If column reaches 9, move to the next row and reset column to 0
    if (col == 9)
    {
        // If row is 8 (last row), the puzzle is solved
        if (row == 8)
        {
            return 1; // Puzzle solved
        }
        row++; // Move to the next row
        col = 0; // Reset column to 0
    }
    
    // If the current cell already has a number, move to the next column
    if (puzzle[row][col] > 0)
    {
        return solve_puzzle(puzzle, row, col + 1);
    }
    
    // Try numbers from 1 to 9 for the current empty cell
    for (int i = 1; i <= 9; i++)
    {
        // Check if the current number is valid in this position
        if (valid_move(puzzel, row, col, i))
        {
            // Place the number in the puzzle
            puzzel[row][col] = i;
            
            // Recursively try to solve the puzzle with the new number
            if (solve_puzzle(puzzel, row, col + 1))
            {
                return 1; // Puzzle solved
            }
            
            // If not solvable, reset the cell and try the next number
            puzzel[row][col] = 0;
        }
    }
    return 0; // If no valid number found, return 0 (backtrack)
}

// Function to check if a move is valid (row, column, and subgrid constraints)
int valid_move(int puzzle[9][9], int row, int col, int val)
{
    // Check if the number already exists in the same row
    for (int i = 0; i < 9; i++)
    {
        if (puzzel[row][i] == val)
        {
            return 0; // Invalid move if found in the row
        }
    }
    
    // Check if the number already exists in the same column
    for (int i = 0; i < 9; i++)
    {
        if (puzzel[i][col] == val)
        {
            return 0; // Invalid move if found in the column
        }
    }
    
    // Check if the number already exists in the 3x3 subgrid
    int r = row - row % 3; // Determine the top-left row of the 3x3 subgrid
    int c = col - col % 3; // Determine the top-left column of the 3x3 subgrid
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[r + i][c + j] == val)
            {
                return 0; // Invalid move if found in the subgrid
            }
        }
    }
    return 1; // Valid move if not found in row, column, or subgrid
}

// Function to print the Sudoku puzzle in a readable format
void print_puzzle(int puzzle[9][9])
{
    // Print the grid borders
    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        // Print a separator line after every 3 rows
        if (row % 3 == 0 && row != 0)
        {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");
        
        // Print each element in the row
        for (int col = 0; col < 9; col++)
        {
            // Print a separator after every 3 columns
            if (col % 3 == 0)
            {
                printf("| ");
            }
            
            // Print the number in the puzzle or an empty space for zeros
            if (puzzel[row][col] != 0)
            {
                printf("%d ", puzzel[row][col]);
            }
            else
            {
                printf("  "); // Print empty space for zeros
            }
        }
        printf("|"); // End of row
    }
    // Print the bottom border of the grid
    printf("\n+-------+-------+-------+\n");		 
}

