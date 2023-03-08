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
    printf("Valide ? %d", is_valid(board, 7, 4, NOIR));
    printBoard(board);

    freeBoard(board);

    return EXIT_SUCCESS;
}