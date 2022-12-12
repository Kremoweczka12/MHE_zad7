#include <vector>
#include <iostream>
#include <random>
#include "puzzle_struct.h"
#include <string>
#include <algorithm>
#include "puzzle_funcs.h"
//
// Created by s23213 on 28.11.2022.
//
int evaluate_puzzle(const puzzle_t puzzle, int &number_of_calls){
    number_of_calls += 1;
    std::vector<std::vector<int>> errors = {};
    std::vector<int> vertical_errors = {};
    std::vector<int> horizontal_errors = {};
    for(int i = 0; i < puzzle.height; i++){

        std::vector<int> values = {};
        int value =0;
        for(int y = 0; y < puzzle.width; y++){

            int elem = puzzle.board[puzzle.width * i + y];
//            std::cout << value << std::endl;
            if(elem == 1){
                value += 1;
            }

            if(elem == 0 or y == puzzle.width - 1){

                if (value != 0){values.push_back(value); }
//                std::cout << value << std::endl;
                value = 0;
            }



        }
        if (values != puzzle.vertical_conditions[i]){
            vertical_errors.push_back(i);
        }
    }
    for(int i = 0; i < puzzle.width; i++){

        std::vector<int> values = {};
        int value =0;
        for(int y = i; y <= (puzzle.width*(puzzle.height- 1)) + i; y+=puzzle.width){
            if ( i == 1) {
                int z = 2;
            }
            int elem = puzzle.board[y];
//            std::cout << value << std::endl;
            if(elem == 1){
                value += 1;
            }

            if(elem == 0 or y == (puzzle.width*(puzzle.height - 1)) + i){

                if (value != 0){values.push_back(value); }
//                std::cout << value << std::endl;
                value = 0;
            }



        }

        if (values != puzzle.horizontal_conditions[i]){
            horizontal_errors.push_back(i);
        }
    }
    errors.push_back(vertical_errors);
    errors.push_back(horizontal_errors);
    int number_of_errors = errors.at(0).size() + errors.at(1).size();
    return number_of_errors;
}



bool next_solution(puzzle_t &puzzle) {
    int i = 0;
    for (; i < puzzle.board.size(); i++) {
        if (puzzle.board[i] == 0) {
            puzzle.board[i] = 1;
            break;
        } else {
            puzzle.board[i] = 0;
        }
    }
    return (i != puzzle.board.size());
}

//int checkout_combinations(int h, int w, std::vector<int> solution){
//    for(int i = 0; i < h*w; i++){
//        std::vector<int> proposed_solution = get_table_comb(h, w);
//        if(solution == proposed_solution){
//            return 1;
//        }
//    }
//}

void full_view(puzzle_t tabela_2, std::string print_calls){
    int n = 0;
    int number_of_calls = 0;
    while (next_solution(tabela_2)) {
        int errors = evaluate_puzzle(tabela_2, number_of_calls);
        if ((n % 128) == 0) {
            std::cout << n << " : " << errors << std::endl << tabela_2 << std::endl;
        }
        if (errors == 0) {
            std::cout << tabela_2 << std::endl;
            break;
        }
        n++;
    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << number_of_calls << " times." << std::endl;
    }

}

puzzle_t get_random_tab(puzzle_t tabela){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1); // define the range
    puzzle_t tab = tabela;
    tab.board = {};
    for(int i = 0; i < tab.height * tab.width;i++){
        int value = distr(gen);
        tab.board.push_back(value);
    }
    return tab;
}

puzzle_t stochastic_method(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls){
    puzzle_t temp_tab = get_random_tab(tabela);
    puzzle_t return_tab = temp_tab;
    int number_of_calls;
    int err = evaluate_puzzle(tabela, number_of_calls);
    for(int i=0; i<iterations; i++){
        temp_tab = get_random_tab(tabela);
        int temp_err = evaluate_puzzle(temp_tab, number_of_calls);
        if(temp_err < err){
            return_tab = temp_tab;
            err = temp_err;
        }
        if(convergence_curve == "yes"){
            std::cout << i << "\t" << err << std::endl;
        }
    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << number_of_calls << " times." << std::endl;
    }
    return return_tab;
}

puzzle_t annealing(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    int number_of_calls = 0;
    int result = evaluate_puzzle(tabela, number_of_calls);
    puzzle_t best_choice = tabela;


    for (int k = 0; k < iterations; k++){
        std::vector<puzzle_t> neighbours = get_neighbours(tabela);

        std::uniform_int_distribution<> distr(0, neighbours.size()); // define the range
        puzzle_t neighbour = neighbours[distr(gen)];

        int new_result = evaluate_puzzle(neighbour, number_of_calls);
        if (new_result < result){
            result = new_result;
            best_choice = neighbour;

        }
        else {
            std::uniform_real_distribution<double> rand(0, 1);
            int temp = new_result-result;
            if (temp < 0){
                temp = temp * -1;
            }
            double Tk = 1000.0/k;
            if (rand(gen) < exp(-1*temp)/Tk) {

                best_choice = neighbour;

            }

        }
            if(convergence_curve == "yes"){
                std::cout << k << "\t" << result << std::endl;
            }

    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << number_of_calls << " times." << std::endl;
    }
    return best_choice;
}


std::vector<puzzle_t> get_neighbours(puzzle_t tabela){
    std::vector<puzzle_t> neighbours = {};
    std::vector<int> neighbours_ids = {};
    for(int i = 0; i < (tabela.width*tabela.height); i++){
//        if (i == tabela.current_point){
//            continue;
//        }
        puzzle_t temp_tab = tabela;
        temp_tab.board[i] = (temp_tab.board[i]+1)%2;
        temp_tab.current_point = i;
        neighbours.push_back(temp_tab);
    }

    return neighbours;
}

puzzle_t stochastic_hill_climbing(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls){
    puzzle_t result = tabela;
    int number_of_calls = 0;
    int err = evaluate_puzzle(tabela, number_of_calls);
    std::vector<puzzle_t> n;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, (tabela.width*tabela.height)-1); // define the range
    puzzle_t great_tab = tabela;
    for(int i = 0; i < iterations; i++){
        n = get_neighbours(great_tab);
        puzzle_t temp_tab = n[distr(gen)];
        great_tab = temp_tab;
        int temp_err = evaluate_puzzle(temp_tab, number_of_calls);
        if(temp_err<err){
            err = temp_err;
            result = temp_tab;
        }
        if(convergence_curve == "yes"){
            std::cout << i << "\t" << err << std::endl;
        }


    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << number_of_calls << " times." << std::endl;
    }
    return result;
}

void pop_front(std::vector<puzzle_t> &v)
{
    if (!v.empty()) {
        v.erase(v.begin());
    }
}


puzzle_t deterministic_hill_climbing(puzzle_t tabela, int iterations, std::string convergence_curve, std::string print_calls){
    puzzle_t result = tabela;
    int calls = 0;
    int err = evaluate_puzzle(tabela, calls);
    std::vector<puzzle_t> n;
    puzzle_t great_tab = tabela;
    int i = 0;
    while (i < iterations){
        n = get_neighbours(great_tab);
        int pre_err = err;
        for(puzzle_t neighbour: n){
            int temp_err = evaluate_puzzle(neighbour, calls);
            if(temp_err<err){
                err = temp_err;
                result = neighbour;
            }
        }
        pre_err = err;

        if (convergence_curve == "yes"){
            std::cout << i << "\t" << err << std::endl;}
        i++;
        great_tab = result;
        if(pre_err==err){
            if(print_calls=="yes"){
                std::cout << "evaluate was called: " << calls << " times." << std::endl;
            }
            return result;

        }

    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << calls << " times." << std::endl;
    }
    return result;
}



puzzle_t tabu_method(puzzle_t tabela, int iterations, int max_size, std::string convergence_curve, std::string print_calls){
    int max_iter = iterations;
    puzzle_t result = tabela;
    puzzle_t grand_result = tabela;
    int calls = 0;
    int err = evaluate_puzzle(tabela, calls);
    int grand_err = err;
    std::vector<puzzle_t> n;
    puzzle_t great_tab = tabela;
    std::vector<puzzle_t> tabu_tab = {};
//    tabu_tab.push_back(tabela);
    while (iterations > 0){
        n = get_neighbours(great_tab);
        int pre_err = err;

        bool c = false;
        int non_visited_n = 0;
        for(puzzle_t neighbour: n){
            if(std::find(tabu_tab.begin(), tabu_tab.end(), neighbour) == tabu_tab.end()) {
                non_visited_n += 1;
                if(!c){
                    c = true;
                    err = evaluate_puzzle(neighbour, calls);
                    result = neighbour;
                    continue;
                }
                int temp_err = evaluate_puzzle(neighbour, calls);
                if(temp_err<err){
                    err = temp_err;
                    result = neighbour;
                }


            }


        }

        if(std::find(tabu_tab.begin(), tabu_tab.end(), result) == tabu_tab.end()) {
            tabu_tab.push_back(result);}
        if (tabu_tab.size() == max_size){
            pop_front(tabu_tab);
            std::cout << " reduction! " << std::endl;
        }

        great_tab = result;
        if(non_visited_n==0){
            std::cout << "its stucked at: " << iterations << " iteration." << std::endl;
            if(print_calls=="yes"){
                std::cout << "evaluate was called: " << calls << " times." << std::endl;
            }
            return grand_result;

        }
        int temp_grand_err = evaluate_puzzle(result, calls);
        if(temp_grand_err < grand_err){
            grand_result = result;
            grand_err = temp_grand_err;
        }
        pre_err = err;
        iterations -= 1;
        if (convergence_curve == "yes"){
            std::cout << max_iter - iterations << "\t" << grand_err << std::endl;}
    }
    if(print_calls=="yes"){
        std::cout << "evaluate was called: " << calls << " times." << std::endl;
    }
    return grand_result;
}