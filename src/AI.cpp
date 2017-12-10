//
// Created by Mathieu on 30/11/2017.
//

#include <iostream>
#include <algorithm>
#include "AI.h"

AI::AI() {
    _end = false;
    for (int y = 0; y < MAP_SIZE; ++y) {
        std::vector<char> mapX;
        std::vector<int> score_mapX;
        for (int x = 0; x < MAP_SIZE; ++x) {
            mapX.push_back('.');
            score_mapX.push_back(12 * Qtuple_info::EMPTY_SCORE);
        }
        map.push_back(mapX);
        score_map.push_back(score_mapX);
    }
}


AI::AI(const AI &ai) {
    map = ai.map;
    score_map = ai.score_map;
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
    for (int y = posY + currI; currI <= 0; ++y, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0) {
                qtuple.convert_to_qtuple(max_consecutive_O);
                max_consecutive_O = 0;
            }
            y = posY + currI;
        }
        if ((y < 0 || y >= MAP_SIZE) || (i == 0 && ((y >= 0 && y < MAP_SIZE && map[y][posX] == playerSymbols[1])
                                                    || (y + 1 >= 0 && y + 1 < MAP_SIZE &&
                                                        map[y + 1][posX] == playerSymbols[1])
                                                    || (y + 2 >= 0 && y + 2 < MAP_SIZE &&
                                                        map[y + 2][posX] == playerSymbols[1])
                                                    || (y + 3 >= 0 && y + 3 < MAP_SIZE &&
                                                        map[y + 3][posX] == playerSymbols[1])
                                                    || (y + 4 >= 0 && y + 4 < MAP_SIZE &&
                                                        map[y + 4][posX] == playerSymbols[1])))) {
            consecutive_n = 0;
            i = -1;
            ++currI;
            y = posY + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
        if (map[y][posX] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][posX] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
        }
    }
    return qtuple;
}


AI::Qtuple_info &AI::find_nb_qtuples_horizontal(
        Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY) {
    int currI = -4;
    int consecutive_n = 0;
    int consecutive_empty = 0;
    int max_consecutive_O = 0;
    int i = 0;
    for (int x = posX + currI; currI <= 0; ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0) {
                qtuple.convert_to_qtuple(max_consecutive_O);
                max_consecutive_O = 0;
            }
            x = posX + currI;
        }
        if ((x < 0 || x >= MAP_SIZE) || (i == 0 && (map[posY][x] == playerSymbols[1]
                                                    || (x + 1 >= 0 && x + 1 < MAP_SIZE &&
                                                        map[posY][x + 1] == playerSymbols[1])
                                                    || (x + 2 >= 0 && x + 2 < MAP_SIZE &&
                                                        map[posY][x + 2] == playerSymbols[1])
                                                    || (x + 3 >= 0 && x + 3 < MAP_SIZE &&
                                                        map[posY][x + 3] == playerSymbols[1])
                                                    || (x + 4 >= 0 && x + 4 < MAP_SIZE &&
                                                        map[posY][x + 4] == playerSymbols[1])))) {
            consecutive_n = 0;
            i = -1;
            ++currI;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
        if (map[posY][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[posY][x] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
        }
    }
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
    for (int y = posY + currI; currI <= 0; ++y, ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0) {
                qtuple.convert_to_qtuple(max_consecutive_O);
                max_consecutive_O = 0;
            }
            y = posY + currI;
            x = posX + currI;
        }
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
            consecutive_n = 0;
            i = -1;
            currI++;
            y = posY + currI - 1;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
        if (map[y][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][x] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
        }
    }
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
    for (int y = posY - currI; currI <= 0; --y, ++x, ++i) {
        if (i == 5) {
            i = 0;
            ++currI;
            if (max_consecutive_O < consecutive_n)
                max_consecutive_O = consecutive_n;
            consecutive_n = 0;
            consecutive_empty = 0;
            if (max_consecutive_O > 0) {
                qtuple.convert_to_qtuple(max_consecutive_O);
                max_consecutive_O = 0;
            }
            y = posY - currI;
            x = posX + currI;
        }
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
            consecutive_n = 0;
            i = -1;
            ++currI;
            y = posY - currI + 1;
            x = posX + currI - 1;
            max_consecutive_O = 0;
            consecutive_empty = 0;
            continue;
        }
        if (map[y][x] == playerSymbols[0]) {
            ++consecutive_n;
            consecutive_empty = 0;
        } else if (map[y][x] == '.') {
            ++consecutive_empty;
            if (consecutive_empty == 5) {
                qtuple.convert_to_qtuple(0);
                consecutive_empty = 0;
            }
        }
    }
    return qtuple;
}

void AI::printMap() {
    bool print_y;
    for (int y = 0; y < MAP_SIZE; ++y) {
        std::cout << y << "  ";
    }
    std::cout << std::endl;
    for (int y = 0; y < MAP_SIZE; ++y) {
        print_y = true;
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (print_y) {
                print_y = false;
                std::cout << y << " ";
            }
            std::cout << map[y][x] << "  ";
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
                    if (playerNb == 2)
                        score_map[posY + y][posX + x] = qtupleOX.comptue_score('O') + qtupleXO.comptue_score('X');
                    else if (playerNb == 1)
                        score_map[posY + y][posX + x] = qtupleOX.comptue_score('X') + qtupleXO.comptue_score('O');
                }
            }
        }
    }
}

Point const &AI::find_best_move() const {
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
    return *p;
}

void AI::update_map(char playerSymbol, int x, int y) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
        map[y][x] = playerSymbol;
        score_map[y][x] = -1;
        positionPlayed = Point(x, y);
    }
}

std::unique_ptr<Point> AI::first_move() const {
    int x = randomRange(4, MAP_SIZE - 4);
    int y = randomRange(4, MAP_SIZE - 4);
    auto p = std::make_unique<Point>(x, y);
    return std::move(p);
}

int AI::randomRange(int min, int max) {
    return min + rand() % (max - min);
}

void AI::signalEnd()
{
    _end = true;
}

const std::vector<std::vector<char>> &AI::getMap() const {
    return map;
}

void AI::setMap(const std::vector<std::vector<char>> &map) {
    AI::map = map;
}

const std::vector<std::vector<int>> &AI::getScoreMap() const {
    return score_map;
}

void AI::setScoreMap(const std::vector<std::vector<int>> &score_map) {
    AI::score_map = score_map;
}

bool AI::isPointPresent(std::vector<Point> const &points, Point const &p) const {
    for (auto &point: points) {
        if (p.x == point.x && p.y == point.y)
            return true;
    }
    return false;
}

std::vector<Point> AI::getBestScoreSquares(int nbSquares) {
    std::vector<Point> points;
    Point p;
    int max_value;
    while (nbSquares > 0) {
        p.x = 0;
        p.y = 0;
        max_value = 0;
        for (int y = 0; y < MAP_SIZE; ++y) {
            for (int x = 0; x < MAP_SIZE; ++x) {
                if (!points.empty()) {
                    if (!isPointPresent(points, Point(x, y)) && max_value <= score_map[y][x]) {
                        max_value = score_map[y][x];
                        p.x = x;
                        p.y = y;
                    }
                } else if (max_value < score_map[y][x]) {
                    max_value = score_map[y][x];
                    p.x = x;
                    p.y = y;
                }
            }
        }
        points.push_back(p);
        --nbSquares;
    }
    return points;
}

int AI::checkStatus() {
    STATUS status = IN_PROGRESS;
    bool draw = true;

    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (score_map[y][x] != -1) {
                draw = false;
            }
            if (score_map[y][x] >= Qtuple_info::OOOO_SCORE) {
                return WIN;
            } else if (score_map[y][x] >= Qtuple_info::XXXX_SCORE) {
                return LOOSE;
            } else if (score_map[y][x] >= Qtuple_info::OOO_SCORE && checkNNNAlignOpening(playerNb == 2 ? 'O' : 'X', x, y)) {
                return WIN;
            } else if (score_map[y][x] >= Qtuple_info::XXX_SCORE && checkNNNAlignOpening(playerNb == 2 ? 'X' : 'O', x, y)) {
                return LOOSE;
            } else {
                status = IN_PROGRESS;
            }
        }
    }
    if (draw)
        status = DRAW;
    return status;
}

const Point &AI::getPositionPlayed() const {
    return positionPlayed;
}

int AI::getPlayerNb() const {
    return playerNb;
}

void AI::setPlayerNb(int playerNb) {
    AI::playerNb = playerNb;
}

bool AI::checkNNNAlignOpening(char playerSymbol, int x, int y) {
    if ((y - 1 >= 0 && y - 1 < MAP_SIZE && map[y - 1][x] == playerSymbol
         && y - 2 >= 0 && y - 2 < MAP_SIZE && map[y - 2][x] == playerSymbol
         && y - 3 >= 0 && y - 3 < MAP_SIZE && map[y - 3][x] == playerSymbol
         && y - 4 >= 0 && y - 4 < MAP_SIZE && map[y - 4][x] == '.'
         && map[y][x] == '.')
        || (y + 1 >= 0 && y + 1 < MAP_SIZE && map[y + 1][x] == playerSymbol
            && y + 2 >= 0 && y + 2 < MAP_SIZE && map[y + 2][x] == playerSymbol
            && y + 3 >= 0 && y + 3 < MAP_SIZE && map[y + 3][x] == playerSymbol
            && y + 4 >= 0 && y + 4 < MAP_SIZE && map[y + 4][x] == '.'
            && map[y][x] == '.')
         || (x - 1 >= 0 && x - 1 < MAP_SIZE && map[y][x - 1] == playerSymbol
             && x - 2 >= 0 && x - 2 < MAP_SIZE && map[y][x - 2] == playerSymbol
             && x - 3 >= 0 && x - 3 < MAP_SIZE && map[y][x - 3] == playerSymbol
             && x - 4 >= 0 && x - 4 < MAP_SIZE && map[y][x - 4] == '.'
             && map[y][x] == '.')
         || (x + 1 >= 0 && x + 1 < MAP_SIZE && map[y][x + 1] == playerSymbol
             && x + 2 >= 0 && x + 2 < MAP_SIZE && map[y][x + 2] == playerSymbol
             && x + 3 >= 0 && x + 3 < MAP_SIZE && map[y][x + 3] == playerSymbol
             && x + 4 >= 0 && x + 4 < MAP_SIZE && map[y][x + 4] == '.'
             && map[y][x] == '.')
         || (x + 1 >= 0 && x + 1 < MAP_SIZE && y + 1 >= 0 && y + 1 < MAP_SIZE &&
             map[y + 1][x + 1] == playerSymbol
             && x + 2 >= 0 && x + 2 < MAP_SIZE && y + 2 >= 0 && y + 2 < MAP_SIZE &&
             map[y + 2][x + 2] == playerSymbol
             && x + 3 >= 0 && x + 3 < MAP_SIZE && y + 3 >= 0 && y + 3 < MAP_SIZE &&
             map[y + 3][x + 3] == playerSymbol
             && x + 4 >= 0 && x + 4 < MAP_SIZE && y + 4 >= 0 && y + 4 < MAP_SIZE && map[y + 4][x + 4] == '.'
             && map[y][x] == '.')
         || (x - 1 >= 0 && x - 1 < MAP_SIZE && y - 1 >= 0 && y - 1 < MAP_SIZE &&
             map[y - 1][x - 1] == playerSymbol
             && x - 2 >= 0 && x - 2 < MAP_SIZE && y - 2 >= 0 && y - 2 < MAP_SIZE &&
             map[y - 2][x - 2] == playerSymbol
             && x - 3 >= 0 && x - 3 < MAP_SIZE && y - 3 >= 0 && y - 3 < MAP_SIZE &&
             map[y - 3][x - 3] == playerSymbol
             && x - 4 >= 0 && x - 4 < MAP_SIZE && y - 4 >= 0 && y - 4 < MAP_SIZE && map[y - 4][x - 4] == '.'
             && map[y][x] == '.')) {
        return true;
    }
    return false;
}
