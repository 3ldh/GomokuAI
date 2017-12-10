//
// Created by 53793 on 07/12/2017.
//

#ifndef GOMOKU_POSITION_H
#define GOMOKU_POSITION_H

struct Point{
    Point (unsigned int xval = 0, unsigned int yval = 0){
        x = xval;
        y = yval;
    }
    unsigned int x;
    unsigned int y;
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ") ";
        return os;
    }
};

#endif //GOMOKU_POSITION_H
