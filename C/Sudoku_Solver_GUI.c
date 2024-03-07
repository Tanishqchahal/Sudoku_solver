#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>

//global variables
#define N 9
int grid[N][N];
GtkWidget *entry[N][N];


void print(int grid[N][N])
{
    // print the grid in the console
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
    // find the empty cell in the grid
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
               
            }
        }
    }
}

bool validInRow(int grid[N][N], int row, int num)
{
    // check if the number is valid in the row
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
    // check if the number is valid in the column
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
    // check if the number is valid in the 3x3 square
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
    // check if the number is valid in the row, column and 3x3 square
    return validInRow(grid, row, num) && validInCol(grid, col, num) && validInSquare(grid, row, col, num);
}

bool solveSudoku(int grid[N][N]) 
{
    // solve the sudoku using backtracking
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

// Function called when Solve button is clicked
void solveButtonClicked(GtkWidget *widget, gpointer data) {
    // Update 'grid' array with values from entry widgets
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            const char *entry_text = gtk_entry_get_text(GTK_ENTRY(entry[i][j]));
            if (entry_text[0] != '\0') {
                grid[i][j] = atoi(entry_text);
            } else {
                grid[i][j] = 0;
            }
        }
    }
    printf("Input grid:\n");
    print(grid);

    // Call the solveSudoku function
    if (solveSudoku(grid)) {
        // Update entry widgets with solved values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char buffer[2];
                sprintf(buffer, "%d", grid[i][j]);
                gtk_entry_set_text(GTK_ENTRY(entry[i][j]), buffer);
            }
        }
        print(grid);
    } else {
        printf("No solution found.\n");
    }
}

// Function called when Reset button is clicked
void resetButtonClicked(GtkWidget *widget, gpointer data) {
    // Clear values in entry widgets and reset 'grid' array
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            gtk_entry_set_text(GTK_ENTRY(entry[i][j]), "");
            grid[i][j] = 0;
        }
    }
}


int main(int argc, char *argv[]) {
    GtkWidget *window, *grid_layout, *solve_button, *reset_button;
    gtk_init(&argc, &argv);

    // Initialize the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku Solver");

    // 10 size distance from the border of outer window.
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    //  The following line of code, closes the app (not just the window opened) from terminal, if you click close
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_set_size_request(window, 600, 700);

    // Create a grid layout for the Sudoku board
    grid_layout = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid_layout);

    // Initialize the Sudoku grid with 0 values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
        }
    }

    // Create entry widgets for user input
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // Create an entry
            entry[i][j] = gtk_entry_new();
            gtk_entry_set_max_length (GTK_ENTRY (entry[i][j]), 1);
            gtk_entry_set_width_chars (GTK_ENTRY (entry[i][j]), 1);
            gtk_entry_set_alignment (GTK_ENTRY (entry[i][j]), 0.5);
            gtk_widget_set_hexpand (entry[i][j], TRUE);
            gtk_widget_set_vexpand (entry[i][j], TRUE);

            // Set font for the entry
            PangoFontDescription *font_desc = pango_font_description_from_string ("15");
            pango_font_description_set_weight (font_desc, PANGO_WEIGHT_BOLD);
            gtk_widget_override_font (entry[i][j], font_desc);

            // Attach the entry to the grid
            gtk_grid_attach (GTK_GRID (grid_layout),entry[i][j], j, i, 1, 1);
        }
    }
    
    // Create Solve button
    solve_button = gtk_button_new_with_label("Solve");
    g_signal_connect(solve_button, "clicked", G_CALLBACK(solveButtonClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid_layout), solve_button, 0, N, N, 1); 

    // Create Reset button
    reset_button = gtk_button_new_with_label("Reset");
    g_signal_connect(reset_button, "clicked", G_CALLBACK(resetButtonClicked), NULL);
    gtk_grid_attach(GTK_GRID(grid_layout), reset_button, 0, N+1, N, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

