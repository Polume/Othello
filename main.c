#include "othello.h"
#include "linked_list.h"
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
    list *go_back = newList(board);

    // board[3][5].color = BLANC;
    // board[3][6].color = BLANC;
    // board[5][1].color = NOIR;
    // board[6][1].color = NOIR;
    // board[6][5].color = NOIR;
    // board[4][7].color = NOIR;
    print_valid(board, NOIR);
    fill(board, 5, 3, NOIR);
    push(&go_back, board);
    fill(board, 3, 2, NOIR);
    push(&go_back, board);

    display_linked_list(go_back);

    printf("\n");

    freeBoard(board);
    free_linked_list(go_back);

    return EXIT_SUCCESS;
}