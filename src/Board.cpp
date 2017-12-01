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
            this->_board[i][j] = EmptyStone;
            ++j;
        }
        ++i;
    }
}

void    Board::clear()
{
    int i = 0;
    int j;

    while (i < WIDTH_BOARD)
    {
        j = 0;
        while (j < WIDTH_BOARD)
        {
            this->_board[i][j] = EmptyStone;
            ++j;
        }
        ++i;
    }
}