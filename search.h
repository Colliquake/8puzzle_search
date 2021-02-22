//
// Created by alexr on 2/18/2021.
//

#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <iostream>
#include "classes.h"
#include <queue>
#include <cmath>

int global_size;

struct compare{
    bool operator()(classes* a, classes* b){      //learned from 'Galik' on https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors
        return ((a->get_depth()+ a->get_weight()) > (b->get_depth()+ b->get_weight()));
    }
};

int findBlank(classes* inp){
    int ret;
    for(int i= 0; i< global_size; i++){
        if(inp->get_board().at(i)== 0){
            ret= i;
        }
    }
    return ret;
}

void MHExpand(classes* inp, int size){
    //TODO: expand for all possible moves
    int global_square= global_size* global_size;        //global_square= (length)^2
    int b= findBlank(inp);
    if(b< global_size){     //blank is in top row
        if(b== 0){          //check if blank is in top-left
            //TODO: valids are right, down
        }
        else if(b== global_size- 1){    //check if blank is top-right
            //TODO: valids are left, down
        }
        else{
            //TODO: valids are left, right, down
        }
    }
    else if((b+ global_size)>= global_square){      //blank is bottom row
        if(b== (global_square- global_size)){       //blank is bottom-left
            //TODO: valids are up, right
        }
        else if(b== (global_square- 1)){        //blank is bottom-left
            //TODO: valids are up, left
        }
        else{
            //TODO: valids are left, right, up
        }
    }
    else if((b% global_size)== 0){      //blank is in first column
        //TODO: valids are up, down, right
    }
    else if(((b+ 1)% n)== 0){       //blank is in last column
        //TODO: valids are up, down, left
    }
    else{       //blanks is not on edge
        //TODO: valids are up, down, left, right
    }
}

int calc_MH(std::vector<int> inp, int n){       //TODO: adapt for size n puzzle
    std::vector<int> solution{1, 2, 3, 4, 5, 6, 7, 8, 0};
    int totalMoves= 0;
    int rowDiff;
    int colDiff;
    int solValLoc;
    for(int i= 0; i< solution.size(), i++){
        if(inp.at(i)== 0){}     //we are on the blank tile of our puzzle; we skip this tile
        if(inp.at(i)!= solution.at(i)){
            solValLoc= inp.at(i)- 1;
            rowDiff= abs(((i/ n)+ 1) - ((solValLoc/ n)+ 1));
            colDiff= abs(((i% n)+ 1) - ((solValLoc% n)+ 1));
            totalMoves+= rowDiff;
            totalMoves+= colDiff;
        }
    }
    return totalMoves;
}

classes* AStarMH(std::vector<int> start, int size){     //TODO: let this program solve for different sizes ("size" represents size of puzzle)
    global_size= size;
    auto* curr= new classes(start, nullptr, 0, calc_MH(start, 3)); //TODO: change 3 to n (length of puzzle)
    int totalNodes= 0;          //TODO
    int maxNodes= 0;            //TODO
    std::priority_queue<classes*, std::vector<classes*>, compare> pq;       //priority queue is a vector consisting of classes pointers
    pq.push(curr);
    while(!pq.empty()){
        curr= pq.top();
        pq.pop();
        if(calc_MH(curr->get_board(), size)== 0){       //we have found solution
            std::cout<< "Done!"<< std::endl;        //TODO: work on description
            return curr;
        }
        MHExpand(curr, size);
    }
}

void select_alg(std::vector<int> v){
    int inp;
    std::cout<< "Select the algorithm you would like to perform (1-3): \n1. Uniform Cost Search\n2. A* with Misplaced Tile heuristic\n3. A* with Manhattan Distance heuristic"<< std::endl;
    std::cin>> inp;
    if(inp== 1){ uniform_cost_search( , );};
    if(inp== 2){ misplaced_tiles( , );};
    if(inp== 3){ std::vector<int> ret_MH= AStarMH(v, 3);};
}

#endif //__SEARCH_H__