#include "graph.h"


//LISTDIGRAPH

ListDigraph::~ListDigraph(){
    for(ListDigraph::NodeIt v_it(*this); v_it.is_valid(); ++v_it){
        //TODO: use OutArcIt later here and undo friend
        for(ListDigraph::Arc* e_ptr : v_it->m_out_arc_ptrs){
            delete e_ptr;
        }
        delete v_it.m_ptr;
    }
}

ListDigraph::Node& ListDigraph::add_node(){
    int id = (this->m_next_node_id)++;
    Node* v_ptr{new Node(id)};
    v_ptr->next = m_first_node_ptr;
    m_first_node_ptr = v_ptr;
    ++m_node_count;
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
    for(ListDigraph::NodeIt v_it(g); v_it.is_valid(); ++v_it){
        out << *v_it << ' ';
    }
    out << std::endl;
    out << "Out arcs:" << std::endl;
    for(ListDigraph::NodeIt v_it(g); v_it.is_valid(); ++v_it){
        out << *v_it << " -> ";
        //need and OutArcIterator here
        out << std::endl;
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
        m_ptr = m_ptr->next;
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
        return *m_ptr;
    } else {
        throw "Invalid iterator";
    }
}

ListDigraph::Node* ListDigraph::NodeIt::operator->(){
    if(is_valid()){
        return m_ptr;
    } else {
        throw "Invalid iterator!";
    }
}


//ARCIT


