#ifndef GRAPH_H
#define GRAPH_H

#include<list>
#include<iostream>

class ListDigraph{
public:
    class Node;
    class NodeIt;
    class Arc;

    ListDigraph()
        : m_next_node_id{0}
        , m_next_arc_id{0}
        , m_arc_count{0}
    {}

    ~ListDigraph();

    ListDigraph(const ListDigraph& v) = delete;

    ListDigraph& operator=(const ListDigraph& v) = delete;

    Node& add_node();

    Arc& add_arc(Node& s, Node& t);

    int node_count() const {return m_node_ptrs.size();}

    int arc_count() const {return m_arc_count;}

    friend std::ostream& operator<<(std::ostream& out, const ListDigraph& g);

private:
    int m_next_node_id;
    int m_next_arc_id;
    std::list<Node*> m_node_ptrs;
    int m_arc_count;
};

class ListDigraph::Node{
private:
    int m_id;
    std::list<ListDigraph::Arc*> m_in_arc_ptrs;
    std::list<ListDigraph::Arc*> m_out_arc_ptrs;

    Node(int id)
        : m_id{id}
        , m_in_arc_ptrs{}
        , m_out_arc_ptrs{}
    {}

public:

    Node(const Node& v) = delete;

    Node& operator=(const Node& v) = delete;

    int id() const {return m_id;}

    friend class ListDigraph;

    friend std::ostream& operator<<(std::ostream& out, const Node& v);
};

class ListDigraph::NodeIt{
private:
    std::list<ListDigraph::Node*>::const_iterator m_it;
    const ListDigraph& m_g;
public:
    NodeIt(const ListDigraph& g)
        : m_it{g.m_node_ptrs.begin()}
        , m_g{g}
    {}

    NodeIt& operator++();

    NodeIt operator++(int);

    Node& operator*();

    Node* operator->();

    NodeIt& operator=(NodeIt& v_it) = delete;

    bool is_valid() const {return m_it != m_g.m_node_ptrs.end();}

    friend class ListDigraph;
};

class ListDigraph::Arc{
private:
    Node& m_source;
    Node& m_target;

public:
    Arc(Node& s, Node& t)
        : m_source{s}
        , m_target{t}
    {}

    Arc(const Arc& e) = delete;

    Arc& operator=(const Arc& v) = delete;

    Node& source() {return m_source;}

    Node& target() {return m_target;}

    friend class ListDigraph;
};

#endif