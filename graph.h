#ifndef GRAPH_H
#define GRAPH_H

#include<list>

class ListDigraph{
public:
    class Node;
    class NodeIt;

    ListDigraph()
        : m_next_node_id{0}
        , m_next_arc_id{0}
    {}

    Node add_node();

    int node_count() const {return nodes.size();}

private:
    int m_next_node_id;
    int m_next_arc_id;
    std::list<Node> nodes;
};

class ListDigraph::Node{
private:
    int m_id;

public:
    Node(ListDigraph& g)
        : m_id{g.m_next_node_id++}
    {}

    int get_id() const {return m_id;}
};

class ListDigraph::NodeIt{
private:
    std::list<ListDigraph::Node>::iterator m_it;
    const ListDigraph& m_g;
public:
    NodeIt(ListDigraph& g)
        : m_it{g.nodes.begin()}
        , m_g{g}
    {}

    NodeIt& operator++();

    NodeIt operator++(int);

    Node& operator*();

    Node* operator->();

    bool is_valid() const {return m_it != m_g.nodes.end();}
};
#endif