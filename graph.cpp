#include <iostream>
#include "graph.h"

// LISTDIGRAPH

ListDigraph::~ListDigraph()
{
    for (NodeIt v_it(*this); v_it.is_valid(); ++v_it)
    {
        for (OutArcIt e_it(*v_it, *this); e_it.is_valid(); ++e_it)
        {
            delete &get_inner(*e_it);
        }
        delete &get_inner(*v_it);
    }
}

Node ListDigraph::add_node()
{
    int id = (this->m_next_node_id)++;
    InnerNode *v_ptr{new InnerNode(id)};
    v_ptr->m_next = m_first_node_ptr;
    if(m_first_node_ptr){
        m_first_node_ptr->m_prev = v_ptr;
    }
    m_first_node_ptr = v_ptr;
    ++m_node_count;
    m_nodes.resize(m_next_node_id);
    m_nodes[id] = v_ptr;
    resize_nodemaps(m_next_node_id);
    return Node(id);
};

Arc ListDigraph::add_arc(Node source, Node target)
{
    if(!is_valid(source) or !is_valid(target)){
        throw "Incalid node!";
    }
    InnerNode &s{get_inner(source)};
    InnerNode &t{get_inner(target)};
    int id = (this->m_next_arc_id)++;
    ListDigraph::InnerArc *e_ptr{new InnerArc(s, t, id)};
    e_ptr->m_next_out = s.m_first_out_arc_ptr;
    if(s.m_first_out_arc_ptr){
        s.m_first_out_arc_ptr->m_prev_out = e_ptr;
    }
    s.m_first_out_arc_ptr = e_ptr;
    ++s.m_out_degree;
    e_ptr->m_next_in = t.m_first_in_arc_ptr;
    if(t.m_first_in_arc_ptr){
        t.m_first_in_arc_ptr->m_prev_in = e_ptr;
    }
    t.m_first_in_arc_ptr = e_ptr;
    ++t.m_in_degree;
    e_ptr->m_next = m_first_arc_ptr;
    if(m_first_arc_ptr){
        m_first_arc_ptr->m_prev =e_ptr;
    }
    m_first_arc_ptr = e_ptr;
    ++m_arc_count;
    m_arcs.resize(m_next_arc_id);
    m_arcs[id] = e_ptr;
    resize_arcmaps(m_next_arc_id);
    return Arc(id);
};

std::ostream &operator<<(std::ostream &out, const ListDigraph &g)
{
    out << "ListDigraph(n=" << g.node_count();
    out << ", m=" << g.arc_count() << ")" << std::endl;
    out << "Nodes: ";
    for (NodeIt v_it(g); v_it.is_valid(); ++v_it)
    {
        out << *v_it << ' ';
    }
    out << std::endl;
    out << "Arcs: ";
    for (ArcIt e_it(g); e_it.is_valid(); ++e_it)
    {
        out << *e_it << ' ';
    }
    out << std::endl;
    out << "Out arcs:" << std::endl;
    for (NodeIt v_it(g); v_it.is_valid(); ++v_it)
    {
        out << *v_it << "(out_degree=";
        out << g.get_inner(*v_it).out_degree() << ") -> ";
        for (OutArcIt e_it(*v_it, g); e_it.is_valid(); ++e_it)
        {
            out << Node(g.get_inner(*e_it).target().id()) << "(id=";
            out << e_it->id() << "), ";
        }
        out << std::endl;
    }
    out << "In arcs:" << std::endl;
    for (NodeIt v_it(g); v_it.is_valid(); ++v_it)
    {
        out << *v_it << "(in_degree=";
        out << g.get_inner(*v_it).in_degree() << ") -> ";
        for (InArcIt e_it(*v_it, g); e_it.is_valid(); ++e_it)
        {
            out << Node(g.get_inner(*e_it).source().id()) << "(id=";
            out << e_it->id() << "), ";
        }
        out << std::endl;
    }
    return out;
}

bool ListDigraph::is_valid(Node v) const {
    if(v.id()<0 or v.id()>=m_next_node_id){
        return false;
    } else {
        return m_nodes[v.id()];
    }
};

bool ListDigraph::is_valid(Arc e) const {
    if(e.id()<0 or e.id()>=m_next_arc_id){
        return false;
    } else {
        return m_arcs[e.id()];
    }
}

Node ListDigraph::source(Arc e) const{
    if(is_valid(e)){
        return this->get_outer(&(this->get_inner(e).source()));
    } else {
        throw "Invalid Arc!";
    }
}

Node ListDigraph::target(Arc e) const{
    if(is_valid(e)){
        return this->get_outer(&(this->get_inner(e).target()));
    } else {
        throw "Invalid Arc!";
    }
}

int ListDigraph::out_degree(Node v) const {
    if(is_valid(v)){
        return this->get_inner(v).out_degree();
    } else{
        throw "Invalid node!";
    }
}

int ListDigraph::in_degree(Node v) const {
    if(is_valid(v)){
        return this->get_inner(v).in_degree();
    } else{
        throw "Invalid node!";
    }
}

ListDigraph::InnerNode& ListDigraph::get_inner(Node v){
    if(is_valid(v)){
        return *m_nodes[v.id()];
    } else {
        throw "Invalid node!";
    }
}

ListDigraph::InnerArc& ListDigraph::get_inner(Arc e){
    if(is_valid(e)){
        return *m_arcs[e.id()];
    } else {
        throw "Invalid arc";
    }
}

const ListDigraph::InnerNode& ListDigraph::get_inner(Node v) const {
    if(is_valid(v)){
        return *m_nodes[v.id()];
    } else {
        throw "Invalid node!";
    }
}

const ListDigraph::InnerArc& ListDigraph::get_inner(Arc e) const {
    if(is_valid(e)){
        return *m_arcs[e.id()];
    } else {
        throw "Invalid arc";
    }
}

Node ListDigraph::get_outer(const InnerNode* v_ptr) const {
    if(v_ptr){
        return Node{v_ptr->id()};
    } else {
        return Node{-1};
    }
}

Arc ListDigraph::get_outer(const InnerArc* e_ptr) const {
    if(e_ptr){
        return Arc{e_ptr->id()};
    } else {
        return Arc{-1};
    }
}

void ListDigraph::resize_nodemaps(int size){
    for(int i=0; i<m_nodemaps.size(); ++i){
        m_nodemaps[i]->resize(size);
    }
}

void ListDigraph::resize_arcmaps(int size){
    for(int i=0; i<m_arcmaps.size(); ++i){
        m_arcmaps[i]->resize(size);
    }
}

// NODE

std::ostream &operator<<(std::ostream &out, Node v)
{
    out << v.id();
    return out;
}

// ARC


std::ostream &operator<<(std::ostream &out, Arc e)
{
    out << e.id();
    return out;
}


// NODEIT

NodeIt &NodeIt::operator++()
{
    if (is_valid())
    {
        m_ptr = m_ptr->m_next;
        m_item = m_g.get_outer(m_ptr);
    }
    return *this;
}

NodeIt NodeIt::operator++(int)
{
    NodeIt temp{*this};
    if (is_valid())
    {
        ++(*this);
    }
    return temp;
}

// OUTARCIT

OutArcIt &OutArcIt::operator++()
{
    if (is_valid())
    {
        m_ptr = m_ptr->m_next_out;
        m_item = m_g.get_outer(m_ptr);
    }
    return *this;
}

OutArcIt OutArcIt::operator++(int)
{
    OutArcIt temp{*this};
    if (is_valid())
    {
        ++(*this);
    }
    return temp;
}

// INARCIT

InArcIt &InArcIt::operator++()
{
    if (is_valid())
    {
        m_ptr = m_ptr->m_next_in;
        m_item = m_g.get_outer(m_ptr);
    }
    return *this;
}

InArcIt InArcIt::operator++(int)
{
    InArcIt temp{*this};
    if (is_valid())
    {
        ++(*this);
    }
    return temp;
}

// ARCIT

ArcIt &ArcIt::operator++()
{
    if (is_valid())
    {
        m_ptr = m_ptr->m_next;
        m_item = m_g.get_outer(m_ptr);
    }
    return *this;
}

ArcIt ArcIt::operator++(int)
{
    ArcIt temp{*this};
    if (is_valid())
    {
        ++(*this);
    }
    return temp;
}

