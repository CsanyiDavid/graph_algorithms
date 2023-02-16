#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <queue>

class BFSIterator{
private:
    const ListDigraph& m_g;
    Node m_current_node;
    std::queue<Node> q;
    NodeMap<int> m_reached_map;
    NodeMap<Arc> m_pred_map;

public:
    BFSIterator(ListDigraph& g, Node s)
        : m_g{g}
        , m_current_node{s}
        , q{}
        , m_reached_map{g, 0}
        , m_pred_map{g, Arc(-1)}
    {
        q.push(s);
    }

    bool is_valid() const {return !q.empty();};

    Node operator*() const {return m_current_node;}

    const Node* operator->() const {return &m_current_node;}

    BFSIterator& operator++();

    BFSIterator operator++(int);

    Arc get_pred_arc() const;
};

class BFS{
private:
    ListDigraph& m_g;
    Node m_s;
    NodeMap<int> m_dist_map;
    NodeMap<int> m_reached_map; //use int instead of bool, because vector<bool> reference doesn't work
    NodeMap<Arc> m_pred_map;

public:
    BFS(ListDigraph& g, Node s)
        : m_g{g}
        , m_s{s}
        , m_dist_map{g, -1}
        , m_reached_map{g, 0}
        , m_pred_map{g, Arc(-1)}
    {}

    void run();

    void set_source(Node s){m_s = s;}

    void clear();

    const NodeMap<int>& dist_map() const {return m_dist_map;}
    const NodeMap<int>& reached_map() const {return m_reached_map;}
    const NodeMap<Arc>& pred_map() const {return m_pred_map;}

};

#endif