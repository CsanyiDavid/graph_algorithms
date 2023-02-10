#include "graph.h"

//LISTDIGRAPH

ListDigraph::Node& ListDigraph::add_node(){
    Node* v_ptr{new Node(*this)};
    m_node_ptrs.push_back(v_ptr);
    return *v_ptr;
};

ListDigraph::Arc& ListDigraph::add_arc(Node& s, Node& t){
    ListDigraph::Arc* e_ptr{new Arc(s, t)};
    s.m_out_arc_ptrs.push_back(e_ptr);
    t.m_in_arc_ptrs.push_back(e_ptr);
    ++m_arc_count;
    return *e_ptr;
};

//NODEIT

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
        return **m_it;
    } else {
        throw "Invalid iterator";
    }
}

ListDigraph::Node* ListDigraph::NodeIt::operator->(){
    if(is_valid()){
        return &(**m_it);
    } else {
        throw "Invalid iterator!";
    }
}

//ARCIT

