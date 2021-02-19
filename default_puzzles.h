//
// Created by alexr on 2/18/2021.
//

#ifndef __DEFAULT_PUZZLES_H__
#define __DEFAULT_PUZZLES_H__

#include <vector>
#include <iostream>

std::vector<int> default_puzzle(int inp){         //input is between 1-8
    std::vector<int> v(9, 0);
    switch(inp){
        case 1:
            v[0]= 1;
            v[1]= 2;
            v[2]= 3;
            v[3]= 4;
            v[4]= 5;
            v[5]= 6;
            v[6]= 7;
            v[7]= 8;
            v[8]= 0;
            break;
        case 2:
            v[0]= 1;
            v[1]= 2;
            v[2]= 3;
            v[3]= 4;
            v[4]= 5;
            v[5]= 6;
            v[6]= 0;
            v[7]= 7;
            v[8]= 8;
            break;
        case 3:
            v[0]= 1;
            v[1]= 2;
            v[2]= 3;
            v[3]= 5;
            v[4]= 0;
            v[5]= 6;
            v[6]= 4;
            v[7]= 7;
            v[8]= 8;
            break;
        case 4:
            v[0]= 1;
            v[1]= 3;
            v[2]= 6;
            v[3]= 5;
            v[4]= 0;
            v[5]= 2;
            v[6]= 4;
            v[7]= 7;
            v[8]= 8;
            break;
        case 5:
            v[0]= 1;
            v[1]= 3;
            v[2]= 6;
            v[3]= 5;
            v[4]= 0;
            v[5]= 7;
            v[6]= 4;
            v[7]= 8;
            v[8]= 2;
            break;
        case 6:
            v[0]= 1;
            v[1]= 6;
            v[2]= 7;
            v[3]= 5;
            v[4]= 0;
            v[5]= 3;
            v[6]= 4;
            v[7]= 8;
            v[8]= 2;
            break;
        case 7:
            v[0]= 7;
            v[1]= 1;
            v[2]= 2;
            v[3]= 4;
            v[4]= 8;
            v[5]= 5;
            v[6]= 6;
            v[7]= 3;
            v[8]= 0;
            break;
        case 8:
            v[0]= 0;
            v[1]= 7;
            v[2]= 2;
            v[3]= 4;
            v[4]= 6;
            v[5]= 1;
            v[6]= 3;
            v[7]= 5;
            v[8]= 8;
            break;
    }
    return v;
}


#endif //__DEFAULT_PUZZLES_H__