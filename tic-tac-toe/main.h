/*****************************************************************************
 * Filename      : main.h
 * Created       : Tue Mar 21 2023
 * Author        : Zolo
 * Github        : https://github.com/zolodev
 * Description   : Header file to order functions for main file
 *****************************************************************************/

#ifndef __main_h__
#define __main_h__

#define PLAYER_ONE_SIGN 'X'
#define PLAYER_TWO_SIGN 'O'

#define GAMECOLORS  // Comment this line to Remove colors

#ifdef GAMECOLORS
#define C_RED "\x1b[31m"
#define C_BLUE "\x1b[34m"
#define C_CYAN "\x1b[44m"
#define C_YELLOW "\x1b[93m"
#define C_MAGENTA "\x1b[35m"
#define C_RESET "\x1b[0m"
#else
#define C_RED ""
#define C_BLUE ""
#define C_CYAN ""
#define C_YELLOW ""
#define C_MAGENTA ""
#define C_RESET ""
#endif

#define ROWS 3
#define COLS 3

char board[ROWS][COLS] = {{' '}};

/*************************************************************
 *
 * Print functions
 *
 *************************************************************/

void clrscr();
void print_intro();
void print_cell(char cell);
void print_game_menu();
void print_draw(int turn);
void print_winner(int turn);
void print_exit_msg();
void print_space_error();

/*************************************************************
 *
 * Board functions
 *
 *************************************************************/
void reset_board();
void render_board();
int update_board(int pos, int turn);

/*************************************************************
 *
 * Game functions
 *
 *************************************************************/
int check_winner(int turn);
int game_loop();
void play_game();

#endif