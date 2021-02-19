//
// Created by alexr on 2/18/2021.
//

#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <iostream>

void select_alg(std::vector<int> v){
    int inp;
    std::cout<< "Select the algorithm you would like to perform (1-3): \n1. Uniform Cost Search\n2. A* with Misplaced Tile heuristic\n3. A* with Manhattan Distance heuristic"<< std::endl;
    std::cin>> inp;
    if(inp== 1){ uniform_cost_search( , );};
    if(inp== 2){ misplaced_tiles( , );};
    if(inp== 3){ manhattan_distance( , ;};
}

#endif //__SEARCH_H__