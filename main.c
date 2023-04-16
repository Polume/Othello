#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();
    // board[0][4].color = NOIR;
    // board[2][3].color = NOIR;
    // board[3][4].color = NOIR;

    // board[1][3].color = BLANC;
    // board[2][2].color = BLANC;
    // board[3][2].color = BLANC;
    // board[3][3].color = BLANC;

    fill(board, 3, 1, NOIR);
    // printBoard(board);
    freeBoard(board);

    return EXIT_SUCCESS;
}