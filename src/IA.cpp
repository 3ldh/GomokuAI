//
// Created by Mathieu on 30/11/2017.
//

#include <iostream>
#include "IA.h"

IA::IA() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        std::vector<char> mapX;
        std::vector<int> score_mapX;
        for (int x = 0; x < MAP_SIZE; ++x) {
            mapX.push_back('.');
            score_mapX.push_back(20 * Qtuple_info::EMPTY_SCORE);
        }
        map.push_back(mapX);
        score_map.push_back(score_mapX);
    }

    map[8][10] = 'X';
    map[9][10] = 'O';
    map[10][10] = '.';
    map[11][10] = 'O';
    map[12][10] = 'O';
    map[13][10] = '.';
    print_map();
}

IA::~IA() = default;

IA::Qtuple_info IA::find_nb_qtuples(int posX, int posY) {
    Qtuple_info qtuple = Qtuple_info();
    int currI = -5;
    int consecutive_O = 0;
    int max_consecutive_O = 0;
    int i = 0;
    bool dot = false;
    for (int y = posY + currI; y + currI != posY + 5 && currI <= 0; ++y, ++i) {
        if (dot) {
            dot = false;
        }
        if (i == 5) {
            i = 0;
            currI++;
            if (max_consecutive_O < consecutive_O)
                max_consecutive_O = consecutive_O;
            consecutive_O = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            y = posY + currI;
            std::cout << std::endl;
        }

        std::cout << "currI : " << currI << " (" << posX << ", " << y << ") ";
        if (y >= 0 && y < MAP_SIZE) {
            if (map[y][posX] == 'O') {
                ++consecutive_O;
                std::cout << " ADD " << consecutive_O << " ";
            } else if (map[y][posX] == 'X') {
                std::cout << " CANCEL AT (" << posX << ", " << y << ") " << std::endl;
                consecutive_O = 0;
                i = -1;
                currI++;
                y = posY + currI - 1;
                max_consecutive_O = -1;
            } else {
                if (max_consecutive_O < consecutive_O)
                    max_consecutive_O = consecutive_O;
                consecutive_O = 0;

                    qtuple.convert_to_qtuple(max_consecutive_O);
                max_consecutive_O = 0;
                dot = true;
            }

        }
    }

    std::cout << std::endl << qtuple << std::endl;

    /*
    for (int x = posX - 5; x < posX + 5; ++x) {
        if (x >= 0 && x < MAP_SIZE && map[posY][x] != 'X') {
            std::cout << "( " << x << ", " << posY << " )" << std::endl;
        }
    }*/
    return qtuple;
}

void IA::print_map() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
}
