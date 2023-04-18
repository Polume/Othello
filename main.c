#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();

    board[3][4].color = NOIR;
    board[5][4].color = NOIR;

    board[3][3].color = BLANC;
    board[4][3].color = BLANC;
    fill(board, 3, 2, NOIR);
    printBoard(board);
    freeBoard(board);

    return EXIT_SUCCESS;
}