#include "default_puzzles.h"
#include "custom_puzzles.h"
#include "search.h"

void select_alg(std::vector<int> v){
    int inp;
    std::cout<< "Select the algorithm you would like to perform (1-3): \n1. Uniform Cost Search\n2. A* with Misplaced Tile heuristic\n3. A* with Manhattan Distance heuristic"<< std::endl;
    std::cin>> inp;
    if(inp== 1){
        clock_t start, end;
        start= clock();
        classes* ret_UC= Uniform_Cost(v, 3);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        std::cout<< "Depth: "<< ret_UC->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds.";
    }
    if(inp== 2){
        clock_t start, end;
        start= clock();
        classes* ret_MT= AStarMis(v, 3);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        std::cout<< "Depth: "<< ret_MT->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds.";
    }
    if(inp== 3){
        clock_t start, end;                             //measuring execution time taken from https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
        start= clock();
        classes* ret_MH= AStarMH(v, 3);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        std::cout<< "Depth: "<< ret_MH->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds.";
    }
}

int main() {
    int P_WIDTH= 3;         //represents "width" of puzzle (e.g. for 3x3, P_WIDTH= 3; for 4x4, P_WIDTH= 4; etc.)
    int x;
    int diff_inp;
    std::cout << "You are using the "<< ((P_WIDTH* P_WIDTH)- 1)<< "-Puzzle Solver. To use a default (pre-made) puzzle, press 1. To enter a custom puzzle, press 2." << std::endl;
    std::cin>> x;
    if(x== 1){              //default puzzle
        std::cout<< "You have selected to solve a default 3x3 puzzle. Please select a difficulty level from 1 to 8 (with 1 being the easiest, to 8 being the most difficult)."<< std::endl;
        std::cin>> diff_inp;
        select_alg(default_puzzle(diff_inp));
    }
    if(x== 2){
        std::string str1, str2, str3;           //TODO: create and implement more str (for when puzzle is larger than 3x3
        std::cout<< "You are entering your own puzzle. Please only enter solvable puzzles. Represent the blank with a '0'."<< std::endl;
        std::cout<< "Enter the first row as one whole number (i.e. don't separate the numbers):"<< std::endl;
        std::cin>> str1;
        std::cout<< "Enter the second row as one whole number:"<< std::endl;
        std::cin>> str2;
        std::cout<< "Enter the third row as one whole number:"<< std::endl;
        std::cin>> str3;
        std::string ret= str1+str2+str3;
        select_alg(custom_puzzle(ret, P_WIDTH));
    }

}