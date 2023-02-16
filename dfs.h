#ifndef DFS_H
#define DFS_H 

#include "graph.h"

class DFSIterator{
private:
    const ListDigraph& m_g;
    Node m_s;
    Node m_current_node;
    Node m_prev_node;
    NodeMap<int> m_reached_map;
    NodeMap<Arc> m_pred_map;
    NodeMap<Node> m_next_node_map;

public:
    DFSIterator(ListDigraph& g, Node s)
        : m_g{g}
        , m_s{s}
        , m_current_node{s}
        , m_prev_node{s}
        , m_reached_map{g, 0}
        , m_pred_map{g, Arc(-1)}
        , m_next_node_map{g, Node(-1)}
    {
        run(m_s);
    }

    void run(Node u);

    bool is_valid() const {return m_g.is_valid(m_current_node);};

    Node operator*() const {return m_current_node;}

    const Node* operator->() const {return &m_current_node;}

    DFSIterator& operator++();

    DFSIterator operator++(int);

    Arc get_pred_arc() const;
};

#endif