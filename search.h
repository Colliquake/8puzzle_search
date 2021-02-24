//
// Created by alexr on 2/18/2021.
//

#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <iostream>
#include "classes.h"
#include <queue>
#include <cmath>
#include <ctime>
#include <bits/stdc++.h>

struct compare{         //orders elements in priority queue by comparing f(n)= (depth)+ weight of each element
    bool operator()(classes* a, classes* b){      //learned from 'Galik' on https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors
        return ((a->get_depth()+ a->get_weight()) > (b->get_depth()+ b->get_weight()));
    }
};

bool seenBefore(std::vector<int> list, std::vector<int> vectorToCheck){     //false if combination is UNIQUE, true if combination was seen before
    std::vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};      //add more primes if puzzle is greater than 5x5
    int current;
    int sum= 0;
    for(int i= 0; i< vectorToCheck.size(); i++){
        current= vectorToCheck.at(i)* primes.at(i);         //creates a uniqueID for each puzzle layout
        sum+= current;
    }
    int flag= 1;            //boolean flag, flag= 0 if combination is not new
    for(int i= 0; i< list.size(); i++){
        if(list.at(i)== sum){
            flag= 0;
        }
    }
    if(flag== 1){
        list.push_back(sum);
        return false;
    }
    return true;
}

int findBlank(classes* inp, int size){          //traverse through board state and find where the blank is
    int ret;
    std::vector<int> vec= inp->get_board();
    for(int i= 0; i< vec.size(); i++){
        if(vec.at(i)== 0){
            ret= i;
        }
    }
    return ret;
}

//void cpyVecToPoint(std::vector<int> copyThis, std::vector<int>* intoThis){
//    for(int i= 0; i< copyThis.size(); i++){
//        intoThis->push_back(copyThis.at(i));
//    }
//}

std::vector<int> makeVecOfSizeN(int n){         //for creating solution puzzles of size n
    int n2= n* n;
    std::vector<int> ret;
    for(int i= 0; i< n2- 1; i++){
        ret.push_back(i+ 1);
    }
    ret.push_back(0);
    return ret;
}

int calc_Mis(std::vector<int> inp, int n){          //calculating Misplaced-Tile heuristic
    std::vector<int> solution= makeVecOfSizeN(n);
    int sum= 0;
    for(int i= 0; i< inp.size(); i++){
        if((inp.at(i)!= 0)&& (inp.at(i)!= solution.at(i))){
            sum++;
        }
    }
    return sum;
}

void UCExpand(classes* inp, int size, std::vector<int> list){               //for expanding all valid moves from current board for Uniform Cost Search
    int global_square= size* size;        //global_square= (length)^2
    int b= findBlank(inp, size);
    std::vector<int> curr= inp->get_board();            //copying board state into a vector
    if(!seenBefore(list, curr)) {               //checks if we have seen current board state before
        if (b < size) {     //blank is in top row
            if (b == 0) {          //check if blank is in top-left
                //valids are right, down
                std::vector<int> r = curr;
                std::swap(r.at(0), r.at(1));
                std::vector<int> d = curr;
                std::swap(d.at(0), d.at(size));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
                inp->add_child(rC);
                classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
                inp->add_child(dC);
            } else if (b == size - 1) {    //check if blank is top-right
                //valids are left, down
                std::vector<int> l = curr;
                std::swap(l.at(size - 1), l.at(size - 2));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
                std::vector<int> d = curr;
                std::swap(d.at(size - 1), d.at(size - 1 + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
                inp->add_child(lC);
                inp->add_child(dC);
            } else {
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
                std::vector<int> d = curr;
                std::swap(d.at(b), d.at(b + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
                inp->add_child(lC);
                inp->add_child(rC);
                inp->add_child(dC);
            }
        } else if ((b + size) >= global_square) {      //blank is in bottom row
            if (b == (global_square - size)) {       //blank is bottom-left
                //valids are up, right
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
                inp->add_child(uC);
                inp->add_child(rC);
            } else if (b == (global_square - 1)) {        //blank is bottom-right
                //valids are up, left
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
                inp->add_child(uC);
                inp->add_child(lC);
            } else {
                //valids are left, right, up
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
                inp->add_child(uC);
                inp->add_child(rC);
                inp->add_child(lC);
            }
        } else if ((b % size) == 0) {      //blank is in first column
            //valids are up, down, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(rC);
        } else if (((b + 1) % size) == 0) {       //blank is in last column
            //valids are up, down, left
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
        } else {       //blanks is not on edge
            //valids are up, down, left, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, 0);
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, 0);
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, 0);
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, 0);
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
            inp->add_child(rC);
        }
    }
}

void MisTileExpand(classes* inp, int size, std::vector<int> list){              //for expanding all valid moves from current board state for A* Search with Misplaced Tile heuristic
    int global_square= size* size;        //global_square= (length)^2
    int b= findBlank(inp, size);
    std::vector<int> curr= inp->get_board();
    if(!seenBefore(list, curr)) {
        if (b < size) {     //blank is in top row
            if (b == 0) {          //check if blank is in top-left
                //valids are right, down
                std::vector<int> r = curr;
                std::swap(r.at(0), r.at(1));
                std::vector<int> d = curr;
                std::swap(d.at(0), d.at(size));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
                inp->add_child(rC);
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
                inp->add_child(dC);
            } else if (b == size - 1) {    //check if blank is top-right
                //valids are left, down
                std::vector<int> l = curr;
                std::swap(l.at(size - 1), l.at(size - 2));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
                std::vector<int> d = curr;
                std::swap(d.at(size - 1), d.at(size - 1 + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
                inp->add_child(lC);
                inp->add_child(dC);
            } else {
                //valids are left, right, down
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
                std::vector<int> d = curr;
                std::swap(d.at(b), d.at(b + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
                inp->add_child(lC);
                inp->add_child(rC);
                inp->add_child(dC);
            }
        } else if ((b + size) >= global_square) {      //blank is in bottom row
            if (b == (global_square - size)) {       //blank is bottom-left
                //valids are up, right
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
                inp->add_child(uC);
                inp->add_child(rC);
            } else if (b == (global_square - 1)) {        //blank is bottom-right
                //valids are up, left
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
                inp->add_child(uC);
                inp->add_child(lC);
            } else {
                //valids are left, right, up
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
                inp->add_child(uC);
                inp->add_child(rC);
                inp->add_child(lC);
            }
        } else if ((b % size) == 0) {      //blank is in first column
            //valids are up, down, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(rC);
        } else if (((b + 1) % size) == 0) {       //blank is in last column
            //valids are up, down, left
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
        } else {       //blanks is not on edge
            //valids are up, down, left, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_Mis(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_Mis(d, size));
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_Mis(l, size));
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_Mis(r, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
            inp->add_child(rC);
        }
    }
}


int calc_MH(std::vector<int> inp, int n){               //calculates the Manhattan heuristic for current board state (represented by vector<int> inp
    std::vector<int> solution= makeVecOfSizeN(n);
    int totalMoves= 0;
    int rowDiff;
    int colDiff;
    int solValLoc;
    for(int i= 0; i< solution.size(); i++){
        if((inp.at(i)!= 0) && (inp.at(i)!= solution.at(i))){        //0 shouldn't have to be moved
            solValLoc= inp.at(i)- 1;
            rowDiff= abs(((i/ n)+ 1) - ((solValLoc/ n)+ 1));
            colDiff= abs(((i% n)+ 1) - ((solValLoc% n)+ 1));
            totalMoves+= rowDiff;
            totalMoves+= colDiff;
        }
    }
    return totalMoves;
}

void MHExpand(classes* inp, int size, std::vector<int> list){      //for expanding all valid moves from current board state for A* Search with Manhattan heuristic
    int global_square= size* size;        //global_square= (length)^2
    int b= findBlank(inp, size);
    std::vector<int> curr= inp->get_board();
    if(!seenBefore(list, curr)) {
        if (b < size) {     //blank is in top row
            if (b == 0) {          //check if blank is in top-left
                //valids are right, down
                std::vector<int> r = curr;
                std::swap(r.at(0), r.at(1));
                std::vector<int> d = curr;
                std::swap(d.at(0), d.at(size));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
                inp->add_child(rC);
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
                inp->add_child(dC);
            } else if (b == size - 1) {    //check if blank is top-right
                //valids are left, down
                std::vector<int> l = curr;
                std::swap(l.at(size - 1), l.at(size - 2));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
                std::vector<int> d = curr;
                std::swap(d.at(size - 1), d.at(size - 1 + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
                inp->add_child(lC);
                inp->add_child(dC);
            } else {
                //valids are left, right, down
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
                std::vector<int> d = curr;
                std::swap(d.at(b), d.at(b + size));
                classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
                inp->add_child(lC);
                inp->add_child(rC);
                inp->add_child(dC);
            }
        } else if ((b + size) >= global_square) {      //blank is in bottom row
            if (b == (global_square - size)) {       //blank is bottom-left
                //valids are up, right
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
                inp->add_child(uC);
                inp->add_child(rC);
            } else if (b == (global_square - 1)) {        //blank is bottom-right
                //valids are up, left
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
                inp->add_child(uC);
                inp->add_child(lC);
            } else {
                //valids are left, right, up
                std::vector<int> u = curr;
                std::swap(u.at(b), u.at(b - size));
                classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
                std::vector<int> r = curr;
                std::swap(r.at(b), r.at(b + 1));
                classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
                std::vector<int> l = curr;
                std::swap(l.at(b), l.at(b - 1));
                classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
                inp->add_child(uC);
                inp->add_child(rC);
                inp->add_child(lC);
            }
        } else if ((b % size) == 0) {      //blank is in first column
            //valids are up, down, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(rC);
        } else if (((b + 1) % size) == 0) {       //blank is in last column
            //valids are up, down, left
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
        } else {       //blanks is not on edge
            //valids are up, down, left, right
            std::vector<int> u = curr;
            std::swap(u.at(b), u.at(b - size));
            classes *uC = new classes(u, inp, inp->get_depth() + 1, calc_MH(u, size));
            std::vector<int> d = curr;
            std::swap(d.at(b), d.at(b + size));
            classes *dC = new classes(d, inp, inp->get_depth() + 1, calc_MH(d, size));
            std::vector<int> l = curr;
            std::swap(l.at(b), l.at(b - 1));
            classes *lC = new classes(l, inp, inp->get_depth() + 1, calc_MH(l, size));
            std::vector<int> r = curr;
            std::swap(r.at(b), r.at(b + 1));
            classes *rC = new classes(r, inp, inp->get_depth() + 1, calc_MH(r, size));
            inp->add_child(uC);
            inp->add_child(dC);
            inp->add_child(lC);
            inp->add_child(rC);
        }
    }
}

classes* AStarMH(std::vector<int> start, int size, int& nodesExpanded, int& maxSize){
    auto* curr= new classes(start, nullptr, 0, calc_MH(start, size));
    int totalNodes= 0;          //for total nodes expanded
    int maxNodes= 0;            //for max queue size
    std::priority_queue<classes*, std::vector<classes*>, compare> pq;       //vector consisting of classes pointers, sorted by comparing f(n)= (depth)+ (weight)
    pq.push(curr);
    maxNodes++;
    std::vector<int> list;
    while(!pq.empty()){
        curr= pq.top();         //looking at top of pq
        pq.pop();
        if(calc_MH(curr->get_board(), size)== 0){       //we have found solution
            std::cout<< "Done with A* Manhattan heuristic!"<< std::endl<< std::endl;
            nodesExpanded= totalNodes;
            maxSize= maxNodes;
            return curr;
        }
        if(pq.size()> maxNodes){
            maxNodes= pq.size();
        }
        MHExpand(curr, size, list);       //expand and put into queue all valid moves from current state (children)
        for(int i= 0; i< curr->get_childSize(); i++) {
            pq.push(curr->get_child(i));
            totalNodes++;
        }
    }
    return nullptr;         //we have no solution
}

classes* AStarMis(std::vector<int> start, int size, int& nodesExpanded, int& maxSize){
    auto* curr= new classes(start, nullptr, 0, calc_Mis(start, size));
    int totalNodes= 0;          //for total nodes expanded
    int maxNodes= 0;            //for max queue size
    std::priority_queue<classes*, std::vector<classes*>, compare> pq;       //vector consisting of classes pointers, sorted by comparing f(n)= (depth)+ (weight)
    pq.push(curr);
    maxNodes++;
    std::vector<int> list;
    while(!pq.empty()){
        curr= pq.top();         //looking at top of pq
        pq.pop();
        if(calc_Mis(curr->get_board(), size)== 0){
            std::cout<< "Done with A* Misplaced Tile heuristic!"<< std::endl<< std::endl;
            nodesExpanded= totalNodes;
            maxSize= maxNodes;
            return curr;
        }
        if(pq.size()> maxNodes){
            maxNodes= pq.size();
        }
        MisTileExpand(curr, size, list);            //expand and put into queue all valid moves from current state
        for(int i= 0; i< curr->get_childSize(); i++){
            pq.push(curr->get_child(i));
            totalNodes++;
        }
    }
    return nullptr;         //we have no solution
}

classes* Uniform_Cost(std::vector<int> start, int size, int& nodesExpanded, int& maxSize){
    auto* curr= new classes(start, nullptr, 0, 0);
    int totalNodes= 0;          //for total nodes expanded
    int maxNodes= 0;            //for max queue size
    std::priority_queue<classes*, std::vector<classes*>, compare> pq;       //pq is a vector consisting of 'classes' pointers, sorted by comparing f(n)= (depth)+ (weight)
    pq.push(curr);
    maxNodes++;
    std::vector<int> list;
    while(!pq.empty()){
        curr= pq.top();         //looking at top of pq
        pq.pop();
        if(calc_Mis(curr->get_board(), size)== 0){          //only uses Misplaced Tiles as a way to check if (board== solution)
            std::cout<< "Done with Uniform Cost Search!"<< std::endl<< std::endl;
            nodesExpanded= totalNodes;
            maxSize= maxNodes;
            return curr;
        }
        if(pq.size()> maxNodes){
            maxNodes= pq.size();
        }
        UCExpand(curr, size, list);         //expand and put into queue all valid moves from current state
        for(int i= 0; i< curr->get_childSize(); i++){
            pq.push(curr->get_child(i));
            totalNodes++;
        }
    }
    return nullptr;         //returns nullptr if we have no solution
}

#endif //__SEARCH_H__