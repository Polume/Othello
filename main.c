#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    // run();
    cell **board = initializeBoard();

    // board[1][0].color = NOIR;
    // board[3][0].color = NOIR;
    // board[4][0].color = NOIR;
    // board[5][0].color = NOIR;
    // board[5][1].color = NOIR;

    board[3][4].color = BLANC;
    board[4][3].color = BLANC;
    easy_mode(board, NOIR);
    // fill(board, 4, 1, BLANC);
    printBoard(board);
    // show_valid(board, BLANC);
    // freeBoard(board);

    return EXIT_SUCCESS;
}