//
// Created by s23213 on 28.11.2022.
//
#include "puzzle_struct.h"
std::ostream &operator<<(std::ostream &o, const puzzle_t &puzzle) {
    for (int y = 0; y < puzzle.height; y++){

        o << "|";
        for (int x = 0; x < puzzle.width; x++){
            auto &val = puzzle.board[y*puzzle.width + x];
            o << "\t" << ((val>0)? "X":" ") << "|";
        }
        o << std::endl;
    }
    return o;
}

bool operator==(puzzle_t l, puzzle_t r) {
    if (l.width != r.width) return false;
    if (l.height!= r.height) return false;
    for (unsigned i = 0; i < r.board.size(); i++) {
        if (l.board.at(i) != r.board.at(i)) return false;
    }
    return true;
}