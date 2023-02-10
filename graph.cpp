#include "graph.h"


//LISTDIGRAPH

ListDigraph::~ListDigraph(){
    ListDigraph::NodeIt v_it(*this);
    while(v_it.is_valid()){
        //TODO: use OutArcIt later here and undo friend
        for(ListDigraph::Arc* e_ptr : v_it->m_out_arc_ptrs){
            delete e_ptr;
        }
        delete *(v_it.m_it);
        ++v_it;
    }
}

ListDigraph::Node& ListDigraph::add_node(){
    int id = (this->m_next_node_id)++;
    Node* v_ptr{new Node(id)};
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

std::ostream& operator<<(std::ostream& out, const ListDigraph& g){
    out << "ListDigraph(n=" << g.node_count();
    out << ", m=" << g.arc_count() << ")" << std::endl;
    out << "Nodes: ";
    ListDigraph::NodeIt v_it(g);
    while(v_it.is_valid()){
        out << *v_it << ' ';
        ++v_it;
    }
    out << std::endl;
    out << "Out arcs:" << std::endl;
    ListDigraph::NodeIt v_it2(g);
    while(v_it2.is_valid()){
        out << *v_it2 << " -> ";
        //need and OutArcIterator here
        out << std::endl;
        ++v_it2;
    }
    return out;
}


//NODE


std::ostream& operator<<(std::ostream& out, const ListDigraph::Node& v){
    out << v.id();
    return out;
}


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


