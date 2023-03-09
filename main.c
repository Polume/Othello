#include "othello.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();
    board[5][4].color = BLANC;
    board[6][4].color = BLANC;
    board[4][2].color = BLANC;
    board[5][2].color = NOIR;
    board[5][5].color = NOIR;
    board[5][6].color = NOIR;

    print_valid(board, NOIR);

    printBoard(board);

    freeBoard(board);

    return EXIT_SUCCESS;
}