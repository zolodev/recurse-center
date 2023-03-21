/*****************************************************************************
 * Filename      : main.c
 * Created       : Tue Mar 21 2023
 * Author        : Zolo
 * Github        : https://github.com/zolodev
 * Description   : This is a terminal Tic-Tac-Toe game for Recurse Center (RC)
 * Website       : https://www.recurse.com/
 *****************************************************************************/

#include <stdio.h>
#include <ctype.h>

#define PLAYER_ONE_SIGN 'X'
#define PLAYER_TWO_SIGN 'O'

#define C_RED "\x1b[31m"
#define C_BLUE "\x1b[34m"
#define C_CYAN "\x1b[44m"
#define C_MAGENTA "\x1b[35m"
#define C_RESET "\x1b[0m"

#define ROWS 3
#define COLS 3

char board[ROWS][COLS] = {{' '}};

void clrscr()
{
    printf("\e[1;1H\e[2J");
}

void print_intro()
{
    printf("\n\n\n");
    printf("--- Tic Tac Toe Game ---\n");
    printf("Instructions\n");
    printf("The game is about to get three in a row horizontal or diagonal.\n");
    printf("Player chose a number between 1-9.\n");
    printf("-------------------------------------\n");
    printf(C_BLUE "Player 1 sign: X\n" C_RESET);
    printf(C_RED "Player 2 sign: O\n" C_RESET);
    printf("To quit the game: q \n");
    printf("-------------------------------------\n");
}

void reset_board()
{
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); i++)
    {
        for (int j = 0; j < sizeof(board) / sizeof(board[i][0]); j++)
        {
            board[i][j] = ' ';
        }
    }
}

void draw_board()
{
    printf("\n");
    printf("\n  -------------------\n");
    // Draw each row
    for (int i = 0; i < 3; i++)
    {
        printf("  |  ");

        // Draw each column
        for (int j = 0; j < 3; j++)
        {
            // Print signs
            if (board[i][j] == PLAYER_ONE_SIGN)
            {
                printf(C_BLUE "%c" C_RESET, board[i][j]);
            }
            else if (board[i][j] == PLAYER_TWO_SIGN)
            {
                printf(C_RED "%c" C_RESET, board[i][j]);
            }
            else
            {
                printf("%c", board[i][j]);
            }

            if (j < 2)
            {
                printf("  |  ");
            }
        }
        printf("  |  ");
        if (i < 2)
        {
            printf("\n  -------------------\n");
        }
    }

    printf("\n  -------------------\n");
}

void print_game_menu()
{
    printf("--- Menu ---\n");
    printf("[R]estart.\n");
    printf("[Q]uit.\n");
    printf("Choice default [R]>");
}

int update_board(int input, int turn)
{
    char sign = (turn % 2 == 0) ? PLAYER_ONE_SIGN : PLAYER_TWO_SIGN;

    // user count from 1-9
    // 1-3 first row, 2-6 second row, 3-9 third row
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    int success = (board[row][col] == ' ');

    if (success)
    {
        board[row][col] = sign;
    }

    return success;
}

int check_winner(int turn)
{
    char sn = (turn % 2 == 0) ? PLAYER_ONE_SIGN : PLAYER_TWO_SIGN;
    int win = 0;

    // Check each row
    win |= ((board[0][0] == sn && board[0][1] == sn && board[0][2] == sn) ||
            (board[1][0] == sn && board[1][1] == sn && board[1][2] == sn) ||
            (board[2][0] == sn && board[2][1] == sn && board[2][2] == sn));

    // Check columns
    win |= ((board[0][0] == sn && board[1][0] == sn && board[2][0] == sn) ||
            (board[0][1] == sn && board[1][1] == sn && board[2][1] == sn) ||
            (board[0][2] == sn && board[1][2] == sn && board[2][2] == sn));

    // Check diagonal
    win |= ((board[0][0] == sn && board[1][1] == sn && board[2][2] == sn) ||
            (board[0][2] == sn && board[1][1] == sn && board[2][0] == sn));

    return win;
}

int play_loop()
{
    char input = ' ';
    int turn = 0;

    reset_board();
    while (turn < 9)
    {
        clrscr();
        draw_board();
        printf("\n\n\n");
        (turn % 2 == 0) ? printf(C_BLUE "Player 1 [X] >" C_RESET)
                        : printf(C_RED "Player 2 [O] >" C_RESET);

        // User place marker
        fgets(&input, sizeof(&input), stdin);

        if (input == 'q')
        {
            clrscr();
            return 1;
        }
        else if ((input - '0') >= 0 && (input - '0') <= 9)
        {
            int success = update_board((input - '0'), turn);

            if (success)
            {
                if (check_winner(turn))
                {
                    clrscr();
                    draw_board();
                    printf("\n\n\n");
                    (turn % 2 == 0) ? printf(C_BLUE "*** Player 1 WINS! ***" C_RESET)
                                    : printf(C_RED "*** Player 2 WINS! ***" C_RESET);
                    printf("\n\n\n");
                    return 0;
                }
            }

            (success) ? turn++
                      : printf("sorry space is taken take another!");
        }
    }

    // Draw
    if (!check_winner(turn))
    {
        clrscr();
        draw_board();
        printf("\n\n\n");
        printf(C_MAGENTA "*** Draw! ***" C_RESET);
        printf("\n\n\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    clrscr();
    print_intro();

    printf("Play tic tac toe? [Y]/n:");
    char input = ' ';
    fgets(&input, sizeof(&input), stdin);

    if (input != 'n')
    {
        int choice = 1;

        do
        {
            if (choice)
            {
                int status = play_loop();
                if (status)
                    printf("Exit game before it was finished...\n");
            }

            print_game_menu();

            fgets(&input, sizeof(&input), stdin);
            choice = (input != 'q');

        } while (choice);
    }

    return 0;
}