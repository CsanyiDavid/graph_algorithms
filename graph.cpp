#include "graph.h"

ListDigraph::Node ListDigraph::add_node(){
    nodes.emplace_back(*this);
    return nodes.back();
};

ListDigraph::NodeIt& ListDigraph::NodeIt::operator++(){
    if(is_valid()){
        ++m_it;
    }
    return *this;
}

ListDigraph::NodeIt ListDigraph::NodeIt::operator++(int){
    NodeIt temp{*this};
    if(is_valid()){
        ++(*this);
    }
    return temp;
}

ListDigraph::Node& ListDigraph::NodeIt::operator*() {
    if(is_valid()){
        return *m_it;
    } else {
        throw "Invalid iterator";
    }
}

ListDigraph::Node* ListDigraph::NodeIt::operator->(){
    if(is_valid()){
        return &(*m_it);
    } else {
        throw "Invalid iterator!";
    }
}