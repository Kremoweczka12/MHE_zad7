//
// Created by s23213 on 28.11.2022.
//

#ifndef UNTITLED_PUZZLE_STRUCT_H

#define UNTITLED_PUZZLE_STRUCT_H

#include <vector>
#include <ostream>

struct puzzle_t {
    int width;
    int height;
    int current_point;
    std::vector<int> board;
    std::vector<std::vector<int>> vertical_conditions;
    std::vector<std::vector<int>> horizontal_conditions;
    int &get(const int x, const int y){
        return board[y*width + x];
    }
    int get(const int x, const int y) const{
        return board.at(y*width + x);
    }
};

std::ostream &operator<<(std::ostream &o, const puzzle_t &puzzle);
bool operator==(puzzle_t l, puzzle_t r);
#endif //UNTITLED_PUZZLE_STRUCT_H

