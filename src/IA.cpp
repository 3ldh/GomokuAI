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

    map[0][0] = 'O';
    map[8][10] = '.';
    map[8][9] = 'O';
    map[9][10] = 'O';
    map[10][8] = 'O';
    map[10][9] = 'O';
    map[7][10] = 'O';
    map[6][9] = 'O';
    map[5][8] = 'O';
    map[4][7] = 'O';
    map[12][7] = '.';
    map[4][15] = '.';
//    map[10][10] = '.';
//    map[11][10] = '.';
//    map[12][10] = 'O';
//    map[13][10] = 'O';
    print_map();
}

IA::~IA() = default;

IA::Qtuple_info &IA::find_nb_qtuples(std::string const &playerSymbols, int posX, int posY) {

    Qtuple_info *qtuple = new Qtuple_info();

    find_nb_qtuples_vertical(*qtuple, playerSymbols, posX, posY);
    find_nb_qtuples_horizontal(*qtuple, playerSymbols, posY, posX);
    find_nb_qtuples_DiagPos(*qtuple, playerSymbols, posX, posY);
    find_nb_qtuples_DiagNeg(*qtuple, playerSymbols, posX, posY);
    return *qtuple;
}

IA::Qtuple_info &IA::find_nb_qtuples_vertical(
        Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY) {
    int currI = -4;
    int consecutive_n = 0;
    int consecutive_empty = 0;
    int max_consecutive_O = 0;
    int i = 0;
    for (int y = posY + currI; y + currI != posY + 5 && currI <= 0; ++y, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            y = posY + currI;
//            std::cout << std::endl;
        }
        //skip iteration if x or y outside the map or if we encounter in the 5 next case the symbol of the opposite player
        if ((y < 0 || y >= MAP_SIZE) || (i == 0 && ((y >= 0 && y < MAP_SIZE && map[y][posX] == playerSymbols[1])
                                                    || (y + 1 >= 0 && y + 1 < MAP_SIZE &&
                                                        map[y + 1][posX] == playerSymbols[1])
                                                    || (y + 2 >= 0 && y + 2 < MAP_SIZE &&
                                                        map[y + 2][posX] == playerSymbols[1])
                                                    || (y + 3 >= 0 && y + 3 < MAP_SIZE &&
                                                        map[y + 3][posX] == playerSymbols[1])
                                                    || (y + 4 >= 0 && y + 4 < MAP_SIZE &&
                                                        map[y + 4][posX] == playerSymbols[1])))) {
//            std::cout << " CANCEL " << std::endl;
            consecutive_n = 0;
            i = -1;
            ++currI;
            y = posY + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
//        std::cout << "currI : " << currI << " (" << posX << ", " << y << ") ";
        if (map[y][posX] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][posX] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            max_consecutive_O = 0;
        }
    }
//    std::cout << std::endl << qtuple << std::endl;
    return qtuple;
}


IA::Qtuple_info &IA::find_nb_qtuples_horizontal(
        Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY) {
    int currI = -4;
    int consecutive_n = 0;
    int consecutive_empty = 0;
    int max_consecutive_O = 0;
    int i = 0;
    for (int x = posX + currI; x + currI != posX + 5 && currI <= 0; ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            x = posX + currI;
//            std::cout << std::endl;
        }
        //skip iteration if x or y outside the map or if we encounter in the 5 next case the symbol of the opposite player
        if ((x < 0 || x >= MAP_SIZE) || (i == 0 && (map[posY][x] == playerSymbols[1]
                                                    || (x + 1 >= 0 && x + 1 < MAP_SIZE &&
                                                        map[posY][x + 1] == playerSymbols[1])
                                                    || (x + 2 >= 0 && x + 2 < MAP_SIZE &&
                                                        map[posY][x + 2] == playerSymbols[1])
                                                    || (x + 3 >= 0 && x + 3 < MAP_SIZE &&
                                                        map[posY][x + 3] == playerSymbols[1])
                                                    || (x + 4 >= 0 && x + 4 < MAP_SIZE &&
                                                        map[posY][x + 4] == playerSymbols[1])))) {
            //  std::cout << " CANCEL " << std::endl;
            consecutive_n = 0;
            i = -1;
            ++currI;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
//        std::cout << "currI : " << currI << " (" << x << ", " << posY << ") ";
        if (map[posY][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[posY][x] == '.') {
            //std::cout << " CANCEL AT (" << posX << ", " << y << ") " << std::endl;
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            max_consecutive_O = 0;
        }
    }
//    std::cout << std::endl << qtuple << std::endl;
    return qtuple;
}

IA::Qtuple_info &IA::find_nb_qtuples_DiagPos(
        IA::Qtuple_info &qtuple, const std::string &playerSymbols, int posX, int posY) {
    int currI = -4;
    int consecutive_n = 0;
    int consecutive_empty = 0;
    int max_consecutive_O = 0;
    int i = 0;
    int x = posX + currI;
    for (int y = posY + currI; y + currI != posY + 5 && x + currI != posX + 5 && currI <= 0; ++y, ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            y = posY + currI;
            x = posX + currI;
//            std::cout << std::endl;
        }
        //skip iteration if x or y outside the map or if we encounter in the 5 next case the symbol of the opposite player
        if ((y < 0 || y >= MAP_SIZE || x < 0 || x >= MAP_SIZE)
            || (i == 0 && ((y >= 0 && y < MAP_SIZE && x >= 0 && x < MAP_SIZE && map[y][x] == playerSymbols[1])
                           || (y + 1 >= 0 && y + 1 < MAP_SIZE && x + 1 >= 0 && x + 1 < MAP_SIZE &&
                               map[y + 1][x + 1] == playerSymbols[1])
                           || (y + 2 >= 0 && y + 2 < MAP_SIZE && x + 2 >= 0 && x + 2 < MAP_SIZE &&
                               map[y + 2][x + 2] == playerSymbols[1])
                           || (y + 3 >= 0 && y + 3 < MAP_SIZE && x + 3 >= 0 && x + 3 < MAP_SIZE &&
                               map[y + 3][x + 3] == playerSymbols[1])
                           || (y + 4 >= 0 && y + 4 < MAP_SIZE && x + 4 >= 0 && x + 4 < MAP_SIZE &&
                               map[y + 4][x + 4] == playerSymbols[1])))) {
//            std::cout << " CANCEL " << std::endl;
            consecutive_n = 0;
            i = -1;
            currI++;
            y = posY + currI - 1;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
//        std::cout << "currI : " << currI << " (" << x << ", " << y << ") ";
        if (map[y][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][x] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            max_consecutive_O = 0;
        }
    }
//    std::cout << std::endl << qtuple << std::endl;
    return qtuple;
}


IA::Qtuple_info &IA::find_nb_qtuples_DiagNeg(
        IA::Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY) {
    int currI = -4;
    int consecutive_n = 0;
    int consecutive_empty = 0;
    int max_consecutive_O = 0;
    int i = 0;
    int x = posX + currI;
    for (int y = posY - currI; y - currI != posY - 5 && x + currI < posX + 5 && currI <= 0; --y, ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            y = posY - currI;
            x = posX + currI;
//            std::cout << std::endl;
        }
        //skip iteration if x or y outside the map or if we encounter in the 5 next case the symbol of the opposite player
        if ((y < 0 || y >= MAP_SIZE || x < 0 || x >= MAP_SIZE)
            || (i == 0 && ((y >= 0 && y < MAP_SIZE && x >= 0 && x < MAP_SIZE && map[y][x] == playerSymbols[1])
                           || (y - 1 >= 0 && y - 1 < MAP_SIZE && x + 1 >= 0 && x + 1 < MAP_SIZE &&
                               map[y - 1][x + 1] == playerSymbols[1])
                           || (y - 2 >= 0 && y - 2 < MAP_SIZE && x + 2 >= 0 && x + 2 < MAP_SIZE &&
                               map[y - 2][x + 2] == playerSymbols[1])
                           || (y - 3 >= 0 && y - 3 < MAP_SIZE && x + 3 >= 0 && x + 3 < MAP_SIZE &&
                               map[y - 3][x + 3] == playerSymbols[1])
                           || (y - 4 >= 0 && y - 4 < MAP_SIZE && x + 4 >= 0 && x + 4 < MAP_SIZE &&
                               map[y - 4][x + 4] == playerSymbols[1])))) {
//            std::cout << " CANCEL " << std::endl;
            consecutive_n = 0;
            i = -1;
            ++currI;
            y = posY - currI + 1;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
//        std::cout << "currI : " << currI << " (" << x << ", " << y << ") ";
        if (map[y][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][x] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            if (max_consecutive_O > 0)
                qtuple.convert_to_qtuple(max_consecutive_O);
            max_consecutive_O = 0;
        }
    }
//    std::cout << std::endl << qtuple << std::endl;
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

void IA::print_score_map() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            std::cout << score_map[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void IA::update_score_map(int posX, int posY) {
    for (int y = -4; y < 5; ++y) {
        for (int x = -4; x < 5; ++x) {
            if (posX + x >= 0 && posX + x < MAP_SIZE && posY + y >= 0 && posY + y < MAP_SIZE) {
                if (map[posY + y][posX + x] == '.') {
                    Qtuple_info qtupleOX = find_nb_qtuples("OX", posX + x, posY + y);
                    Qtuple_info qtupleXO = find_nb_qtuples("XO", posX + x, posY + y);
                    score_map[posY + y][posX + x] = qtupleOX.comptue_score('O') + qtupleXO.comptue_score('X');
                } else {
                    score_map[posY + y][posX + x] = -1;
                }
            }
        }
    }
    print_score_map();
}




