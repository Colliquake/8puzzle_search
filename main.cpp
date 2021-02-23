#include "default_puzzles.h"
#include "custom_puzzles.h"
#include "search.h"
#include <stack>

void display_vector(classes* inp, int size){
    for(int i= 0; i< size; i++){
        for(int j= 0; j< size; j++){
            std::cout<< inp->get_board().at(i* size+ j)<< "\t";
        }
        std::cout<< std::endl;
    }
}

void display_trace(classes* last_step, int size){
    std::stack<classes*> list;
    for(classes* ptr= last_step; ptr!= nullptr; ptr= ptr->get_parent_pointer()){
        list.push(ptr);
    }
    while(!list.empty()){
        display_vector(list.top(), size);
        std::cout<< "This state has a cost g(n) = "<< list.top()->get_depth()<< " and a heuristic h(n) = "<< list.top()->get_weight()<< ". The best state to expand to is:"<< std::endl;
        list.pop();
    }
    std::cout<< "None! We have reached the goal state."<< std::endl;
}

void select_alg(std::vector<int> v){
    int inp;
    std::cout<< "Select the algorithm you would like to perform (1-3): \n1. Uniform Cost Search\n2. A* with Misplaced Tile heuristic\n3. A* with Manhattan Distance heuristic"<< std::endl;
    std::cin>> inp;

    if(inp== 1){
        int size= 3;        //change for different puzzle sizes
        int nodesExpanded, maxSize;
        clock_t start, end;
        start= clock();
        classes* ret_UC= Uniform_Cost(v, size, nodesExpanded, maxSize);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        display_trace(ret_UC, size);
        std::cout<< "Depth: "<< ret_UC->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds."<< std::endl;
        std::cout<< "Total nodes expanded: "<< nodesExpanded<< std::endl;
        std::cout<< "Maximum size of queue: "<< maxSize<< std::endl;
    }
    if(inp== 2){
        int size= 3;
        int nodesExpanded, maxSize;
        clock_t start, end;
        start= clock();
        classes* ret_MT= AStarMis(v, size, nodesExpanded, maxSize);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        display_trace(ret_MT, size);
        std::cout<< "Depth: "<< ret_MT->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds."<< std::endl;
        std::cout<< "Total nodes expanded: "<< nodesExpanded<< std::endl;
        std::cout<< "Maximum size of queue: "<< maxSize<< std::endl;
    }
    if(inp== 3){
        int size= 3;
        int nodesExpanded, maxSize;
        clock_t start, end;                             //measuring execution time taken from https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
        start= clock();
        classes* ret_MH= AStarMH(v, size, nodesExpanded, maxSize);
        end= clock();
        double tot_time= double(end- start)/ double(CLOCKS_PER_SEC);
        display_trace(ret_MH, size);
        std::cout<< "Depth: "<< ret_MH->get_depth()<< std::endl;
        std::cout<< "Total execution time is "<< std::fixed<< std::setprecision(6)<< tot_time;
        std::cout<< " seconds."<< std::endl;
        std::cout<< "Total nodes expanded: "<< nodesExpanded<< std::endl;
        std::cout<< "Maximum size of queue: "<< maxSize<< std::endl;
    }
}

int main() {
    int P_LENGTH= 3;         //represents "length" of puzzle (e.g. for 3x3, P_WIDTH= 3; for 4x4, P_WIDTH= 4; etc.)
    int x;
    int diff_inp;
    std::cout << "You are using the "<< ((P_LENGTH* P_LENGTH)- 1)<< "-Puzzle Solver. To use a default (pre-made) puzzle, press 1. To enter a custom puzzle, press 2." << std::endl;
    std::cin>> x;
    if(x== 1){              //default puzzle
        std::cout<< "You have selected to solve a default 3x3 puzzle. Please select a difficulty level from 1 to 8 (with 1 being the easiest, to 8 being the most difficult)."<< std::endl;
        std::cin>> diff_inp;
        select_alg(default_puzzle(diff_inp));
    }
    if(x== 2){
        std::string length, str1, str2, str3;
        std::cout<< "Please enter the size of your puzzle (enter '3' for a 3x3 puzzle, enter '4' for a 4x4, etc.): ";
        std::cin>> length;
        P_LENGTH= stoi(length);
        std::cout<< "You are entering your own puzzle. Please only enter solvable puzzles. Represent the blank with a '0'."<< std::endl;
        std::cout<< "Enter the first row as one whole number (i.e. don't separate the numbers):"<< std::endl;
        std::cin>> str1;
        std::cout<< "Enter the second row as one whole number:"<< std::endl;
        std::cin>> str2;
        std::cout<< "Enter the third row as one whole number:"<< std::endl;     //add more options for puzzles larger than 3x3
        std::cin>> str3;
        std::string ret= str1+str2+str3;
        select_alg(custom_puzzle(ret, P_LENGTH));
    }

}