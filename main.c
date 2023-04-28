#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    run();
    // cell **board = initializeBoard();

    // board[3][2].color = NOIR;
    // board[3][3].color = NOIR;
    // board[3][4].color = NOIR;

    // board[4][2].color = BLANC;
    // board[4][3].color = BLANC;
    // board[4][4].color = BLANC;

    // fill(board, 2, 4, BLANC);
    // printBoard(board);
    // show_valid(board, BLANC);

    return EXIT_SUCCESS;
}