//
// Created by alexr on 2/18/2021.
//

#ifndef __CUSTOM_PUZZLES_H__
#define __CUSTOM_PUZZLES_H__

#include <string>

std::vector<int> custom_puzzle(std::string str, int length){        //converts inputs from user into a puzzle in the form of a vector
    int area= length* length;
    std::vector<int> v(area, 0);
    for(int i= 0; i< area; i++){
        v[i]= ((int)str[i] - 48);      //ascii to int
    }
    return v;
}

#endif //__CUSTOM_PUZZLES_H__