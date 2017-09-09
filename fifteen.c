/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9
#define BLANK_TILE 0

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// tiles
int tile;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int *a, int *b);
int linear_search(int target, int array[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // board dimensions
    tile = (d * d) - 1;

    // draws board //
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            board[i][j] = tile;
            tile = tile - 1;
        }
    }

    // sets invisible int for "blank" tile //
    board[d-1][d-1] = BLANK_TILE;

    // d is odd; switch tiles 1 and 2 //
    if ((d % 2) == 0) {
        swap(&board[d-1][d-2], &board[d-1][d-3]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == BLANK_TILE) {
                printf("  _");
            } else {
            printf("%3i", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    if (tile < 1 && tile > (d * d) - 1) {
        return false;
    }

    int row;
    int col;

    // Find given number's index in array //
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {

            if (board[i][j] == tile) {
                row = i;
                col = j;
            }
        }
    }

    // check above and move if legal //
    if ((row - 1) >= 0 && board[row - 1][col] == BLANK_TILE) {
        board[row - 1][col] = board[row][col];
        board[row][col] = BLANK_TILE;

        return true;

    }

    // check below and move if legal //
    else if ((row + 1) < d && board[row + 1][col] == BLANK_TILE) {
        board[row + 1][col] = board[row][col];
        board[row][col] = BLANK_TILE;

        return true;
    }


    // check left and move if legal //
    else if ((col - 1) >= 0 && board[row][col - 1] == BLANK_TILE) {
        board[row][col - 1] = board[row][col];
        board[row][col] = BLANK_TILE;

        return true;
    }


    // check right and move if legal //
    else if ((col + 1) < d && board[row][col + 1] == BLANK_TILE) {
        board[row][col + 1] = board[row][col];
        board[row][col] = BLANK_TILE;

        return true;
    }

    // illegal move //
    else {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 * Correct configuration is an increasing order from left to right and top to bottom.
 */
bool won(void)
{
    int current = 1;

    /**
     * Iterate over array and check values.
     * If any single value is incorrect, return false.
     * If every value is correct, return true.
     */
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != current)
            {
                return false;
            }
            else if (board[i][j] == current && current < (d * d))
            {
                current++;
                if ((current == (d * d) - 1) && board[d-1][d-1] == BLANK_TILE)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Returns index of target int in an array
 */
int linear_search(int target, int array[]) {
    for (int i = 0; i < d; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return false;
}