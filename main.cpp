#include <iostream>
#include <string>
#include "json.hpp"
#include "puzzle_struct.h"
#include <fstream>
#include "puzzle_funcs.h"



int main(int argc, char** argv) {
    std::string method = argv[1];
    int iter = std::stoi(argv[2]);
    std::string file_name = argv[3];
    int max_size = std::stoi(argv[4]);
    std::string display_time = argv[5];
    std::ifstream file_input(file_name, std::ifstream::binary);
    nlohmann::json data = nlohmann::json::parse(file_input);
    std::string display_solution = argv[6];
    std::string display_solution_quality = argv[7];
// wyświetlanie lub nie krzywej zbieżności
    std::string convergence_curve = argv[8];
    std::string calls_number_print = argv[9];




//    puzzle_t tabela_4;
//    tabela_4.width = 5;
//    tabela_4.height = 5;
//
//    tabela_4.board = {
//            0,0,0,0,0,
//            0, 0, 0,0,0,
//            0, 0, 0, 0, 0,
//            0,0,0,0,0,
//            0,0,0,0,0,
//    };
//    tabela_4.horizontal_conditions = data["h"];
//    tabela_4.vertical_conditions = data["v"];

    puzzle_t tabela_4;
    tabela_4.width = 10;
    tabela_4.height = 10;

    tabela_4.board = {
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
    };
    tabela_4.horizontal_conditions = data["h"];
    tabela_4.vertical_conditions = data["v"];


    auto start = std::chrono::steady_clock::now();
    auto minor_start = std::chrono::steady_clock::now();
    if(method=="compare"){
        puzzle_t tab = get_random_tab(tabela_4);
        int c = 0;
        minor_start = std::chrono::steady_clock::now();
        puzzle_t tab_3 = annealing(tab, iter, convergence_curve, calls_number_print);
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}
        std::cout << "annaeling result: " << evaluate_puzzle(tab_3, c) << std::endl;
        auto minor_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = minor_end-minor_start;
        std::cout << "finished in time: " << elapsed_seconds.count() << "s\n";

        minor_start = std::chrono::steady_clock::now();
        tab_3 = deterministic_hill_climbing(tab, iter, convergence_curve, calls_number_print);
        minor_end = std::chrono::steady_clock::now();
        elapsed_seconds = minor_end-minor_start;
        std::cout << "finished in time: " << elapsed_seconds.count() << "s\n";
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}
        std::cout << "deterministic hill climbing result: " << evaluate_puzzle(tab_3, c) << std::endl;

        minor_start = std::chrono::steady_clock::now();
        tab_3 = stochastic_hill_climbing(tab, iter, convergence_curve, calls_number_print);
        minor_end = std::chrono::steady_clock::now();
        elapsed_seconds = minor_end-minor_start;
        std::cout << "finished in time: " << elapsed_seconds.count() << "s\n";

        if (display_solution_quality == "yes"){
            std::cout << "stochastic hill climbing found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}

        minor_start = std::chrono::steady_clock::now();
        tab_3 = stochastic_method(tab, iter, convergence_curve, calls_number_print);
        minor_end = std::chrono::steady_clock::now();
        elapsed_seconds = minor_end-minor_start;
        std::cout << "finished in time: " << elapsed_seconds.count() << "s\n";
        if (display_solution_quality == "yes"){
            std::cout << "pure stochastic method found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}

        minor_start = std::chrono::steady_clock::now();
        tab_3 = tabu_method(tab, iter, max_size, convergence_curve, calls_number_print);
        minor_end = std::chrono::steady_clock::now();
        elapsed_seconds = minor_end-minor_start;
        std::cout << "finished in time: " << elapsed_seconds.count() << "s\n";
        if (display_solution_quality == "yes"){
            std::cout << "tabu method found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}


    }
    if(method=="a"){
        puzzle_t tab = get_random_tab(tabela_4);
        puzzle_t tab_3 = annealing(tab, iter, convergence_curve, calls_number_print);
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}

    }
    if(method=="d"){
        puzzle_t tab = get_random_tab(tabela_4);
        puzzle_t tab_3 = deterministic_hill_climbing(tab, iter, convergence_curve, calls_number_print);

        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}

    }
    if(method=="sh"){
        puzzle_t tab = get_random_tab(tabela_4);
        puzzle_t tab_3 = stochastic_hill_climbing(tab, iter, convergence_curve, calls_number_print);
        int c = 0;
        if (display_solution_quality == "yes"){
            std::cout << "found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}
    }
    if(method=="p"){
        full_view(tabela_4, calls_number_print);
    }
    if(method=="s"){
        puzzle_t tab = get_random_tab(tabela_4);
        int c = 0;
        puzzle_t tab_3 = stochastic_method(tab, iter, convergence_curve, calls_number_print);
        if (display_solution_quality == "yes"){
            std::cout << "found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}
    }
    if(method=="t"){
        puzzle_t tab = get_random_tab(tabela_4);
        int c = 0;
        puzzle_t tab_3 = tabu_method(tab, iter, max_size, convergence_curve, calls_number_print);
        if (display_solution_quality == "yes"){
            std::cout << "found solution has: " << evaluate_puzzle(tab_3, c) << " errors." << std::endl;
        }
        if (display_solution == "yes"){std::cout << tab_3 << std::endl;}
    }
    if (display_time=="yes"){
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }



    return 0;
}
