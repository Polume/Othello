#include "othello.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    run();
    cell **plateau = initializeBoard();
    plateau[4][2].color = 2;
    fill_lines(plateau, 4, 2, 4);
    printBoard(plateau);

    return EXIT_SUCCESS;
}