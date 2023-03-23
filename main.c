#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();

    board[1][4].color = BLANC;
    board[2][4].color = NOIR;
    board[3][4].color = BLANC;
    board[4][4].color = NOIR;

    // board[5][2].color = NOIR;
    // board[5][5].color = NOIR;
    // board[5][6].color = NOIR;

    // board[3][6].color = BLANC;
    // board[5][1].color = NOIR;
    // board[6][1].color = NOIR;
    // board[6][5].color = NOIR;
    // board[4][7].color = NOIR;
    // print_valid(board, NOIR);
    printBoard(board);
    fill(board, 5, 4, BLANC);
    printBoard(board);
    printf("\n");

    freeBoard(board);

    return EXIT_SUCCESS;
}