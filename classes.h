//
// Created by alexr on 2/21/2021.
//

#ifndef __CLASSES_H__
#define __CLASSES_H__


class classes{              //able to use this one node/class for all three search functions
private:
    std::vector<int> curr_board;
    classes* parent;           //points to parent (mainly for tracing)
    std::vector<classes*> children;    //vector consisting of pointers to children (no more than 4)
    int depth;
    int weight;     //heuristic function
public:
    classes(std::vector<int> inp, classes* par, int dep, int wei) {
        curr_board = inp;
        parent = par;
        depth = dep;
        weight = wei;
    }

    std::vector<int> get_board(){
        return curr_board;
    }

    classes* get_parent_pointer(){
        return parent;
    }

    void set_parent_ptr(classes* parPtr){
        parent= parPtr;
    }

    std::vector<classes*> get_children() {
        return children;
    }

    classes* get_child(int i){
        return children.at(i);
    }

    int get_childSize(){
        return children.size();
    }

    void add_child(classes* inp){
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