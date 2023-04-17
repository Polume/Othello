#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();

    // board[2][3].color = NOIR;
    // board[3][4].color = NOIR;

    // board[3][2].color = BLANC;
    // board[3][3].color = BLANC;
    freeBoard(board);

    return EXIT_SUCCESS;
}