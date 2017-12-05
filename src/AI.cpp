//
// Created by Mathieu on 30/11/2017.
//

#include <iostream>
#include "AI.h"

AI::AI() {
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

  /*  map[10][10] = 'O';
    map[10][11] = 'O';
    map[10][12] = 'O';
    map[11][10] = 'X';
    map[11][11] = 'X';
    map[11][12] = 'X';
    map[11][13] = 'X';

    update_score_map(10, 10);;
    update_score_map(11, 10);
    update_score_map(11, 10);
    update_score_map(12, 10);
    update_score_map(10, 11);
    update_score_map(11, 11);
    update_score_map(12, 11);
    print_map();

    update_score_map(14, 11);
    find_best_move();*/
}

AI::~AI() = default;

AI::Qtuple_info &AI::find_nb_qtuples(std::string const &playerSymbols, int posX, int posY) {

    Qtuple_info *qtuple = new Qtuple_info();

    find_nb_qtuples_vertical(*qtuple, playerSymbols, posX, posY);
    find_nb_qtuples_horizontal(*qtuple, playerSymbols, posX, posY);
    find_nb_qtuples_DiagPos(*qtuple, playerSymbols, posX, posY);
    find_nb_qtuples_DiagNeg(*qtuple, playerSymbols, posX, posY);
    return *qtuple;
}

AI::Qtuple_info &AI::find_nb_qtuples_vertical(
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


AI::Qtuple_info &AI::find_nb_qtuples_horizontal(
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

AI::Qtuple_info &AI::find_nb_qtuples_DiagPos(
        AI::Qtuple_info &qtuple, const std::string &playerSymbols, int posX, int posY) {
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


AI::Qtuple_info &AI::find_nb_qtuples_DiagNeg(
        AI::Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY) {
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

void AI::print_map() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void AI::print_score_map() {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            std::cout << score_map[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void AI::update_score_map(int posX, int posY) {
    for (int y = -4; y < 5; ++y) {
        for (int x = -4; x < 5; ++x) {
            if (posX + x >= 0 && posX + x < MAP_SIZE && posY + y >= 0 && posY + y < MAP_SIZE) {
                if (map[posY + y][posX + x] == '.') {
                    Qtuple_info qtupleOX = find_nb_qtuples("OX", posX + x, posY + y);
                    Qtuple_info qtupleXO = find_nb_qtuples("XO", posX + x, posY + y);
                    score_map[posY + y][posX + x] = qtupleOX.comptue_score('O') + qtupleXO.comptue_score('X');
                }
            }
        }
    }
//    print_score_map();
}

AI::Point const &AI::find_best_move() const {
    Point *p = new Point();
    int max_value = 0;

    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (max_value < score_map[y][x]) {
                max_value = score_map[y][x];
                p->x = x;
                p->y = y;
            } else if (max_value == score_map[y][x]) {
                if (rand() % 2 > 0) {
                    p->x = x;
                    p->y = y;
                }
            }
        }
    }
//    std::cout << p->x << ", " << p->y << std::endl;
    return *p;
}

void AI::update_map(char playerSymbol, int x, int y) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
        map[y][x] = playerSymbol;
        score_map[y][x] = -1;
       /* if (playerSymbol == 'O')
            print_map();*/
    }
}

