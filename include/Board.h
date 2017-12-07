//
// Created by Edouard on 29/11/2017.
//

#ifndef GOMOKU_BOARD_H
#define GOMOKU_BOARD_H

#define WIDTH_BOARD 19

struct Board{
    enum TypeStone{
        EmptyStone = 0,
        OurStone,
        TheirStone,
        NbTypeStone
    };
    TypeStone _board[WIDTH_BOARD][WIDTH_BOARD];

    Board();
    void reset();
};

#endif //GOMOKU_BOARD_H
