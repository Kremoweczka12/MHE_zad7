//
// Created by s23213 on 28.11.2022.
//

#ifndef UNTITLED_PUZZLE_FUNCS_H
#define UNTITLED_PUZZLE_FUNCS_H

#include <vector>
#include "puzzle_struct.h"

int evaluate_puzzle(const puzzle_t puzzle, int &number_of_calls);

puzzle_t annealing(puzzle_t tabela, int iterations,
                   std::string convergence_curve, std::string print_calls);

bool next_solution(puzzle_t &puzzle);

void full_view(puzzle_t tabela_2, std::string print_calls);

puzzle_t get_random_tab(puzzle_t tabela);

puzzle_t stochastic_method(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls);
std::vector<puzzle_t> get_neighbours(puzzle_t tabela);

puzzle_t stochastic_hill_climbing(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls);

void pop_front(std::vector<puzzle_t> &v);


puzzle_t deterministic_hill_climbing(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls);


puzzle_t tabu_method(puzzle_t tabela, int iterations, int max_size, std::string convergence_curve, std::string print_calls);
#endif //UNTITLED_PUZZLE_FUNCS_H
