#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **board = initializeBoard();
    board[2][1].color = NOIR;
    board[0][2].color = NOIR;
    board[1][2].color = NOIR;
    board[2][2].color = NOIR;
    board[3][2].color = NOIR;
    board[4][2].color = NOIR;
    board[5][2].color = NOIR;
    board[2][3].color = NOIR;
    board[4][3].color = NOIR;
    board[2][4].color = NOIR;
    board[2][5].color = NOIR;

    board[1][1].color = BLANC;
    board[4][1].color = BLANC;
    board[3][3].color = BLANC;
    board[3][4].color = BLANC;
    board[3][5].color = BLANC;
    board[4][4].color = BLANC;
    board[4][5].color = BLANC;

    fill(board, 3, 1, BLANC);
    // print_valid(board, NOIR);
    printBoard(board);
    freeBoard(board);

    return EXIT_SUCCESS;
}