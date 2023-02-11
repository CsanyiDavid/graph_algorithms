#include<iostream>
#include "graph.h"


//LISTDIGRAPH

ListDigraph::~ListDigraph(){
    for(ListDigraph::NodeIt v_it(*this); v_it.is_valid(); ++v_it){
        for(ListDigraph::OutArcIt e_it(*v_it); e_it.is_valid(); ++e_it){
            delete e_it.m_ptr;
        }
        delete v_it.m_ptr;
    }
}

ListDigraph::Node& ListDigraph::add_node(){
    int id = (this->m_next_node_id)++;
    Node* v_ptr{new Node(id)};
    v_ptr->m_next = m_first_node_ptr;
    m_first_node_ptr = v_ptr;
    ++m_node_count;
    return *v_ptr;
};

ListDigraph::Arc& ListDigraph::add_arc(Node& s, Node& t){
    ListDigraph::Arc* e_ptr{new Arc(s, t)};
    e_ptr->m_next_out = s.m_first_out_arc_ptr;
    s.m_first_out_arc_ptr = e_ptr;
    ++s.out_degree;
    e_ptr->m_next_in = t.m_first_in_arc_ptr;
    t.m_first_in_arc_ptr = e_ptr;
    ++t.in_degree;
    ++m_arc_count;
    return *e_ptr;
};

std::ostream& operator<<(std::ostream& out, const ListDigraph& g){
    out << "ListDigraph(n=" << g.node_count();
    out << ", m=" << g.arc_count() << ")" << std::endl;
    out << "Nodes: ";
    for(ListDigraph::NodeIt v_it(g); v_it.is_valid(); ++v_it){
        out << *v_it << ' ';
    }
    out << std::endl;
    out << "Out arcs:" << std::endl;
    for(ListDigraph::NodeIt v_it(g); v_it.is_valid(); ++v_it){
        out << *v_it << " -> ";
        for(ListDigraph::OutArcIt e_it(*v_it); e_it.is_valid(); ++e_it){
            out << e_it->target() << ' ';
        }
        out << std::endl;
    }
    return out;
}


//NODE


std::ostream& operator<<(std::ostream& out, const ListDigraph::Node& v){
    out << v.id();
    return out;
}


//ARC


//NODEIT


ListDigraph::NodeIt& ListDigraph::NodeIt::operator++(){
    if(is_valid()){
        m_ptr = m_ptr->m_next;
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


//OUTARCIT


ListDigraph::OutArcIt& ListDigraph::OutArcIt::operator++(){
    if(is_valid()){
        m_ptr = m_ptr->m_next_out;
    }
    return *this;
}

ListDigraph::OutArcIt ListDigraph::OutArcIt::operator++(int){
    OutArcIt temp{*this};
    if(is_valid()){
        ++(*this);
    }
    return temp;
}


//INARCIT


ListDigraph::InArcIt& ListDigraph::InArcIt::operator++(){
    if(is_valid()){
        m_ptr = m_ptr->m_next_in;
    }
    return *this;
}

ListDigraph::InArcIt ListDigraph::InArcIt::operator++(int){
    InArcIt temp{*this};
    if(is_valid()){
        ++(*this);
    }
    return temp;
}