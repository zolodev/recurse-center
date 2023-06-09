/*****************************************************************************
 * Filename      : main.c
 * Created       : Tue Mar 21 2023
 * Author        : Zolo
 * Github        : https://github.com/zolodev
 * Description   : This is a terminal Tic-Tac-Toe game for Recurse Center (RC)
 * Website       : https://www.recurse.com/
 *****************************************************************************/

#include "main.h"

#include <ctype.h>
#include <stdio.h>

/*************************************************************
 *
 * Print functions
 *
 *************************************************************/

void clrscr() { printf("\e[1;1H\e[2J"); }

void print_intro() {
  printf("\n\n\n");
  printf("--- Tic Tac Toe Game ---\n");
  printf("\n");
  printf("Instructions\n");
  printf("Player should try to get three in a row.\n");
  printf("Player choose a number between 1-9.\n");
  printf("\n");
  printf("-------------------------------------\n");
  printf("\n");
  printf(C_BLUE "Player 1 sign: X\n" C_RESET);
  printf(C_RED "Player 2 sign: O\n" C_RESET);
  printf("To quit the game: q \n");
  printf("\n");
  printf("-------------------------------------\n");
}

void print_cell(char cell) {
  switch (cell) {
    case PLAYER_ONE_SIGN:
      printf(C_BLUE "%c" C_RESET, cell);
      break;

    case PLAYER_TWO_SIGN:
      printf(C_RED "%c" C_RESET, cell);
      break;

    default:
      printf("%c", cell);
      break;
  }
}

void print_game_menu() {
  printf("--- Menu ---\n");
  printf("[R]estart.\n");
  printf("[Q]uit.\n");
  printf("Choice default [R]>");
}

void print_draw(int turn) {
  clrscr();
  render_board();
  printf("\n\n\n");
  printf(C_MAGENTA "*** Draw! ***" C_RESET);
  printf("\n\n\n");
}

void print_winner(int turn) {
  clrscr();
  render_board();
  printf("\n");
  (turn % 2 == 0) ? printf(C_BLUE "*** Player 1 WINS! ***" C_RESET)
                  : printf(C_RED "*** Player 2 WINS! ***" C_RESET);
  printf("\n\n\n");
}

void print_exit_msg() {
  printf(C_MAGENTA "Exited game before it was finished...\n" C_RESET);
}

void print_space_error() {
  printf(C_YELLOW "Sorry cell space is taken take by a sign!" C_RESET);
}

/*************************************************************
 *
 * Board functions
 *
 *************************************************************/

void reset_board() {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      board[row][col] = ' ';
    }
  }
}

void render_board() {
  printf(BOARD_HORIZONTAL_LINE);

  // Draw each row
  for (int row = 0; row < ROWS; row++) {
    printf(BOARD_VERTICAL_LINE);

    // Draw each column
    for (int col = 0; col < COLS; col++) {
      // Print signs
      print_cell(board[row][col]);

      printf(BOARD_VERTICAL_LINE);
    }

    printf(BOARD_HORIZONTAL_LINE);
  }
}

int update_board(int pos, int turn) {
  char sign = (turn % 2 == 0) ? PLAYER_ONE_SIGN : PLAYER_TWO_SIGN;

  // user count from 1-9
  // 1-3 first row, 2-6 second row, 3-9 third row
  int row = (pos - 1) / 3;
  int col = (pos - 1) % 3;

  return (board[row][col] == ' ') ? board[row][col] = sign : 0;
}

/*************************************************************
 *
 * Game functions
 *
 *************************************************************/

int check_winner(int turn) {
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

int game_loop() {
  char input = ' ';
  int turn = 0;
  int space_busy = 0;

  reset_board();
  do {
    clrscr();
    render_board();

    if (space_busy) {
      print_space_error();
      space_busy = 0;
    }

    (turn % 2 == 0) ? printf(C_BLUE "\nPlayer 1 [X] >" C_RESET)
                    : printf(C_RED "\nPlayer 2 [O] >" C_RESET);

    // User place marker
    fgets(&input, sizeof(&input), stdin);

    if (input == 'q') {
      clrscr();
      return 1;
    } else if ((input - '0') >= 0 && (input - '0') <= 9) {
      int success = update_board((input - '0'), turn);

      if (success) {
        if (check_winner(turn)) {
          print_winner(turn);
          return 0;
        }

        turn++;
      }

      space_busy = !success;
    }
  } while (turn < MAX_TURNS);

  print_draw(turn);

  return 0;
}

void play_game() {
  char input = ' ';
  do {
    if (game_loop()) print_exit_msg();

    print_game_menu();
    input = fgetc(stdin);

  } while (input != 'q');
}

int main(int argc, char *argv[]) {
  clrscr();
  print_intro();

  printf("Play tic tac toe? [Y]/n/q:");
  char input = fgetc(stdin);

  // Close application if user do not want to play
  if (input == 'n' || input == 'q') return 0;

  play_game();

  return 0;
}