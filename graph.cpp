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
    RealNode *v_ptr{new RealNode(id)};
    v_ptr->m_next = m_first_node_ptr;
    if(m_first_node_ptr){
        m_first_node_ptr->m_prev = v_ptr;
    }
    m_first_node_ptr = v_ptr;
    ++m_node_count;
    nodes.resize(m_next_node_id);
    nodes[id] = v_ptr;
    return Node(id);
};

Arc ListDigraph::add_arc(Node source, Node target)
{
    RealNode &s{get_inner(source)};
    RealNode &t{get_inner(target)};
    int id = (this->m_next_arc_id)++;
    ListDigraph::RealArc *e_ptr{new RealArc(s, t, id)};
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
    arcs.resize(m_next_arc_id);
    arcs[id] = e_ptr;
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
        ListDigraph::RealNode *v_ptr{m_g.get_inner(m_item).m_next};
        if (v_ptr)
        {
            m_item = Node(v_ptr->id());
        }
        else
        {
            m_item = Node{-1};
        }
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
        ListDigraph::RealArc *e_ptr{m_g.get_inner(m_item).m_next_out};
        if (e_ptr)
        {
            m_item = Arc(e_ptr->id());
        }
        else
        {
            m_item = Arc{-1};
        }
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
        ListDigraph::RealArc *e_ptr{m_g.get_inner(m_item).m_next_in};
        if (e_ptr)
        {
            m_item = Arc(e_ptr->id());
        }
        else
        {
            m_item = Arc{-1};
        }
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
        ListDigraph::RealArc *e_ptr{m_g.get_inner(m_item).m_next};
        if (e_ptr)
        {
            m_item = Arc{e_ptr->id()};
        }
        else
        {
            m_item = Arc{-1};
        }
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