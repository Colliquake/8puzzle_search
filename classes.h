//
// Created by alexr on 2/21/2021.
//

#ifndef __CLASSES_H__
#define __CLASSES_H__


class classes{
private:
    std::vector<int> curr_board;
    std::vector<int>* parent;           //points to parent
    std::vector<std::vector<int>*> children;    //vector consisting of pointers to children (no more than 4)
    int depth;
    int weight;     //for f(n)
public:
    classes(std::vector<int> inp, std::vector<int>* par, int dep, int wei) {
        curr_board = inp;
        parent = par;
        depth = dep;
        weight = wei;
    }

    std::vector<int> get_board(){
        return curr_board;
    }

    std::vector<int>* get_parent_pointer(){
        return parent;
    }

    std::vector<std::vector<int>*> get_children() {
        return children;
    }

    void add_child(std::vector<int>* inp){
        children.push_back(inp);
    }

    void set_depth(int d){
        depth= d;
    }

    void set_weight(int w){
        weight= w;
    }

    int get_depth(){
        return depth;
    }

    int get_weight(){
        return weight;
    }
};


#endif