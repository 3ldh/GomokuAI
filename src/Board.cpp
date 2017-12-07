//
// Created by Edouard on 29/11/2017.
//

#include "Board.h"

Board::Board()
{
    int i = 0;
    int j;

    while (i < WIDTH_BOARD)
    {
        j = 0;
        while (j < WIDTH_BOARD)
        {
            _board[i][j] = EmptyStone;
            ++j;
        }
        ++i;
    }
}

void    Board::reset()
{
    int i = 0;
    int j;

    while (i < WIDTH_BOARD)
    {
        j = 0;
        while (j < WIDTH_BOARD)
        {
            _board[i][j] = EmptyStone;
            ++j;
        }
        ++i;
    }
}