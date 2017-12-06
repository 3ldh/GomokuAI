//
// Created by Mathieu on 30/11/2017.
//

#ifndef GOMOKU_IA_H
#define GOMOKU_IA_H


#include <vector>
#include <iostream>
#include <memory>

class AI {

    struct Qtuple_info {

        static const int EMPTY_SCORE = 7;
        static const int X_SCORE = 15;
        static const int XX_SCORE = 400;
        static const int XXX_SCORE = 1800;
        static const int XXXX_SCORE = 100000;
        static const int O_SCORE = 35;
        static const int OO_SCORE = 800;
        static const int OOO_SCORE = 15000;
        static const int OOOO_SCORE = 800000;

        int empty_nb;
        int n_nb;
        int nn_nb;
        int nnn_nb;
        int nnnn_nb;

        explicit Qtuple_info(int empty_nb = 0, int o_nb = 0, int oo_nb = 0, int ooo_nb = 0, int oooo_nb = 0) :
                empty_nb(empty_nb), n_nb(o_nb), nn_nb(oo_nb), nnn_nb(ooo_nb), nnnn_nb(oooo_nb) {};

        void convert_to_qtuple(int i) {
            switch (i) {
                case 0:
                    empty_nb += 1;
                    break;
                case 1:
                    n_nb += 1;
                    break;
                case 2:
                    nn_nb += 1;
                    break;
                case 3:
                    nnn_nb += 1;
                    break;
                case 4:
                    nnnn_nb += 1;
                    break;
                default:
                    break;
            }
        }

        int comptue_score(const char playerSymbol) const {
            if (playerSymbol == 'O')
                return empty_nb * EMPTY_SCORE + n_nb * O_SCORE + nn_nb * OO_SCORE + nnn_nb * OOO_SCORE +
                       nnnn_nb * OOOO_SCORE;
            else if (playerSymbol == 'X')
                return n_nb * X_SCORE + nn_nb * XX_SCORE + nnn_nb * XXX_SCORE + nnnn_nb * XXXX_SCORE;
            else
                return 0;
        }

        friend std::ostream &operator<<(std::ostream &os, const Qtuple_info &q) {
            os << "empty_nb : " << q.empty_nb << " o_nb : " << q.n_nb << " oo_nb : " << q.nn_nb << " ooo_nb "
               << q.nnn_nb << " oooo_nb : " << q.nnnn_nb;
            return os;
        }
    };

    static const int MAP_SIZE = 19;

public:
    struct Point {
        int x;
        int y;

        Point(int x = 0, int y = 0) : x(x), y(y) {};
    };

private :
    std::vector<std::vector<char>> map;
    std::vector<std::vector<int>> score_map;

    int randomRange(int min, int max) const;
    void print_score_map();
    void print_map();
    Qtuple_info &find_nb_qtuples_vertical(Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY);
    Qtuple_info &find_nb_qtuples_horizontal(Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY);
    Qtuple_info &find_nb_qtuples_DiagPos(Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY);
    Qtuple_info &find_nb_qtuples_DiagNeg(Qtuple_info &qtuple, std::string const &playerSymbols, int posX, int posY);
    Qtuple_info &find_nb_qtuples(std::string const &playerSymbols, int posX, int posY);

public:
    AI();
    virtual ~AI();
    void update_score_map(int posX, int posY);
    Point const &find_best_move() const;
    void update_map(char playerSymbol, int x, int y);
    std::unique_ptr<Point> first_move() const;
};



#endif //GOMOKU_IA_H
