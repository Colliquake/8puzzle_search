//
// Created by alexr on 2/18/2021.
//

#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <iostream>
#include "classes.h"
#include <queue>
#include <cmath>

struct compare{
    bool operator()(classes* a, classes* b){      //learned from 'Galik' on https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors
        return ((a->get_depth()+ a->get_weight()) > (b->get_depth()+ b->get_weight()));
    }
};

int findBlank(classes* inp, int size){
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


int calc_MH(std::vector<int> inp, int n){       //TODO: adapt for size n puzzle
    std::vector<int> solution{1, 2, 3, 4, 5, 6, 7, 8, 0};
    int totalMoves= 0;
    int rowDiff;
    int colDiff;
    int solValLoc;
    for(int i= 0; i< solution.size(); i++){
//        if(inp.at(i)== 0){}     //we are on the blank tile of our puzzle; we skip this tile
        if((inp.at(i)!= 0) && (inp.at(i)!= solution.at(i))){
            solValLoc= inp.at(i)- 1;
            rowDiff= abs(((i/ n)+ 1) - ((solValLoc/ n)+ 1));
            colDiff= abs(((i% n)+ 1) - ((solValLoc% n)+ 1));
            totalMoves+= rowDiff;
            totalMoves+= colDiff;
        }
    }
    return totalMoves;
}

void MHExpand(classes* inp, int size){      //add children pointers (vector pointers) to inp
    //expand for all possible moves
    int global_square= size* size;        //global_square= (length)^2
    int b= findBlank(inp, size);
    std::vector<int> curr= inp->get_board();
    if(b< size){     //blank is in top row
        if(b== 0){          //check if blank is in top-left
            //valids are right, down
//            std::vector<int>* rightPoint= new std::vector<int>;
//            std::vector<int>* downPoint= new std::vector<int>;
//            cpyVecToPoint(curr, rightPoint);
//            cpyVecToPoint(curr, downPoint);
//            std::swap(rightPoint->at(0), rightPoint->at(1));
//            std::swap(downPoint->at(0), downPoint->at(global_size));
            std::vector<int> r= curr;
            std::swap(r.at(0), r.at(1));
            std::vector<int> d= curr;
            std::swap(d.at(0), d.at(size));
            classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
            inp->add_child(rC);
            classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
            inp->add_child(dC);
        }
        else if(b== size- 1){    //check if blank is top-right
            //valids are left, down
//            std::vector<int>* leftPoint= new std::vector<int>;
//            std::vector<int>* downPoint= new std::vector<int>;
//            cpyVecToPoint(curr, leftPoint);
//            cpyVecToPoint(curr, downPoint);
//            std::swap(leftPoint->at(global_size- 1), leftPoint->at(global_size- 2));
//            std::swap(downPoint->at(global_size- 1), downPoint->at(global_size- 1+ global_size));
            std::vector<int> l= curr;
            std::swap(l.at(size- 1), l.at(size- 2));
            classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
            std::vector<int> d= curr;
            std::swap(d.at(size- 1), d.at(size- 1+ size));
            classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
            inp->add_child(lC);
            inp->add_child(dC);
        }
        else{
            //valids are left, right, down
//            std::vector<int>* leftPoint= new std::vector<int>;
//            std::vector<int>* rightPoint= new std::vector<int>;
//            std::vector<int>* downPoint= new std::vector<int>;
//            cpyVecToPoint(curr, leftPoint);
//            cpyVecToPoint(curr, rightPoint);
//            cpyVecToPoint(curr, downPoint);
//            std::swap(leftPoint->at(b), leftPoint->at(b- 1));
//            std::swap(rightPoint->at(b), rightPoint->at(b+ 1));
//            std::swap(downPoint->at(b), downPoint->at(b+ global_size));

            std::vector<int> l= curr;
            std::swap(l.at(b), l.at(b- 1));
            classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
            std::vector<int> r= curr;
            std::swap(r.at(b), r.at(b+ 1));
            classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
            std::vector<int> d= curr;
            std::swap(d.at(b), d.at(b+ size));
            classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
            inp->add_child(lC);
            inp->add_child(rC);
            inp->add_child(dC);
        }
    }
    else if((b+ size)>= global_square){      //blank is bottom row
        if(b== (global_square- size)){       //blank is bottom-left
            //valids are up, right
//            std::vector<int>* upPoint= new std::vector<int>;
//            std::vector<int>* rightPoint= new std::vector<int>;
//            cpyVecToPoint(curr, upPoint);
//            cpyVecToPoint(curr, rightPoint);
//            std::swap(upPoint->at(b), upPoint->at(b- global_size));
//            std::swap(rightPoint->at(b), rightPoint->at(b+ 1));

            std::vector<int> u= curr;
            std::swap(u.at(b), u.at(b- size));
            classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
            std::vector<int> r= curr;
            std::swap(r.at(b), r.at(b+ 1));
            classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
            inp->add_child(uC);
            inp->add_child(rC);
        }
        else if(b== (global_square- 1)){        //blank is bottom-right
            //valids are up, left
//            std::vector<int>* upPoint= new std::vector<int>;
//            std::vector<int>* leftPoint= new std::vector<int>;
//            cpyVecToPoint(curr, upPoint);
//            cpyVecToPoint(curr, leftPoint);
//            std::swap(upPoint->at(b), upPoint->at(b- global_size));
//            std::swap(leftPoint->at(b), leftPoint->at(b- 1));

            std::vector<int> u= curr;
            std::swap(u.at(b), u.at(b- size));
            classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
            std::vector<int> l= curr;
            std::swap(l.at(b), l.at(b- 1));
            classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
            inp->add_child(uC);
            inp->add_child(lC);
        }
        else{
            //valids are left, right, up
//            std::vector<int>* upPoint= new std::vector<int>;
//            std::vector<int>* rightPoint= new std::vector<int>;
//            std::vector<int>* leftPoint= new std::vector<int>;
//            cpyVecToPoint(curr, upPoint);
//            cpyVecToPoint(curr, rightPoint);
//            cpyVecToPoint(curr, leftPoint);
//            std::swap(upPoint->at(b), upPoint->at(b- global_size));
//            std::swap(rightPoint->at(b), rightPoint->at(b+ 1));
//            std::swap(leftPoint->at(b), leftPoint->at(b- 1));

            std::vector<int> u= curr;
            std::swap(u.at(b), u.at(b- size));
            classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
            std::vector<int> r= curr;
            std::swap(r.at(b), r.at(b+ 1));
            classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
            std::vector<int> l= curr;
            std::swap(l.at(b), l.at(b- 1));
            classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
            inp->add_child(uC);
            inp->add_child(rC);
            inp->add_child(lC);
        }
    }
    else if((b% size)== 0){      //blank is in first column
        //valids are up, down, right
//        std::vector<int>* upPoint= new std::vector<int>;
//        std::vector<int>* downPoint= new std::vector<int>;
//        std::vector<int>* rightPoint= new std::vector<int>;
//        cpyVecToPoint(curr, upPoint);
//        cpyVecToPoint(curr, downPoint);
//        cpyVecToPoint(curr, rightPoint);
//        std::swap(upPoint->at(b), upPoint->at(b- global_size));
//        std::swap(downPoint->at(b), downPoint->at(b+ global_size));
//        std::swap(rightPoint->at(b), rightPoint->at(b+ 1));

        std::vector<int> u= curr;
        std::swap(u.at(b), u.at(b- size));
        classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
        std::vector<int> d= curr;
        std::swap(d.at(b), d.at(b+ size));
        classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
        std::vector<int> r= curr;
        std::swap(r.at(b), r.at(b+ 1));
        classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
        inp->add_child(uC);
        inp->add_child(dC);
        inp->add_child(rC);
    }
    else if(((b+ 1)% size)== 0){       //blank is in last column
        //valids are up, down, left
//        std::vector<int>* upPoint= new std::vector<int>;
//        std::vector<int>* downPoint= new std::vector<int>;
//        std::vector<int>* leftPoint= new std::vector<int>;
//        cpyVecToPoint(curr, upPoint);
//        cpyVecToPoint(curr, downPoint);
//        cpyVecToPoint(curr, leftPoint);
//        std::swap(upPoint->at(b), upPoint->at(b- global_size));
//        std::swap(downPoint->at(b), downPoint->at(b+ global_size));
//        std::swap(leftPoint->at(b), leftPoint->at(b- 1));

        std::vector<int> u= curr;
        std::swap(u.at(b), u.at(b- size));
        classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
        std::vector<int> d= curr;
        std::swap(d.at(b), d.at(b+ size));
        classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
        std::vector<int> l= curr;
        std::swap(l.at(b), l.at(b- 1));
        classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
        inp->add_child(uC);
        inp->add_child(dC);
        inp->add_child(lC);
    }
    else{       //blanks is not on edge
        //valids are up, down, left, right
//        std::vector<int>* upPoint= new std::vector<int>;
//        std::vector<int>* downPoint= new std::vector<int>;
//        std::vector<int>* leftPoint= new std::vector<int>;
//        std::vector<int>* rightPoint= new std::vector<int>;
//        cpyVecToPoint(curr, upPoint);
//        cpyVecToPoint(curr, downPoint);
//        cpyVecToPoint(curr, leftPoint);
//        cpyVecToPoint(curr, rightPoint);
//        std::swap(upPoint->at(b), upPoint->at(b- global_size));
//        std::swap(downPoint->at(b), downPoint->at(b+ global_size));
//        std::swap(leftPoint->at(b), leftPoint->at(b- 1));
//        std::swap(rightPoint->at(b), rightPoint->at(b+ 1));

        std::vector<int> u= curr;
        std::swap(u.at(b), u.at(b- size));
        classes* uC= new classes(u, inp, inp->get_depth()+ 1, calc_MH(u, size));
        std::vector<int> d= curr;
        std::swap(d.at(b), d.at(b+ size));
        classes* dC= new classes(d, inp, inp->get_depth()+ 1, calc_MH(d, size));
        std::vector<int> l= curr;
        std::swap(l.at(b), l.at(b- 1));
        classes* lC= new classes(l, inp, inp->get_depth()+ 1, calc_MH(l, size));
        std::vector<int> r= curr;
        std::swap(r.at(b), r.at(b+ 1));
        classes* rC= new classes(r, inp, inp->get_depth()+ 1, calc_MH(r, size));
        inp->add_child(uC);
        inp->add_child(dC);
        inp->add_child(lC);
        inp->add_child(rC);
    }
}

classes* AStarMH(std::vector<int> start, int size){     //TODO: let this program solve for different sizes ("size" represents size of puzzle)
    auto* curr= new classes(start, nullptr, 0, calc_MH(start, size));
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
        MHExpand(curr, size);       //children pointers have been added
        for(int i= 0; i< curr->get_childSize(); i++) {
            pq.push(curr->get_child(i));
        }
    }
    return nullptr;
}

#endif //__SEARCH_H__