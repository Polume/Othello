#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();
    board[3][3].color = BLANC;
    board[3][4].color = BLANC;
    board[3][5].color = BLANC;
    board[2][3].color = BLANC;
    board[0][5].color = NOIR;

    board[3][7].color = NOIR;

    // board[2][3].color = NOIR;
    // board[3][4].color = NOIR;

    printBoard(board);
    printf("%d ", is_valid(board, 3, 2, NOIR));
    fill(board, 3, 2, NOIR);

    // board[3][2].color = BLANC;
    // board[3][3].color = BLANC;
    printBoard(board);
    freeBoard(board);

    return EXIT_SUCCESS;
}