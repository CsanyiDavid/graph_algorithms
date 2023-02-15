#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <queue>

class BFS{
private:
    const ListDigraph& m_g;
    Node m_s;
    NodeMap<int> m_dist_map;
    NodeMap<int> m_reached_map; //use int instead of bool, because vector<bool> reference doesn't work
    NodeMap<int> m_processed_map;
    NodeMap<Arc> m_pred_map;

public:
    BFS(ListDigraph& g, Node s)
        : m_g{g}
        , m_s{s}
        , m_dist_map{g, -1}
        , m_reached_map{g, 0}
        , m_processed_map{g, 0}
        , m_pred_map{g, Arc(-1)}
    {}

    void run();

    const NodeMap<int>& dist_map() const {return m_dist_map;}
    const NodeMap<int>& reached_map() const {return m_reached_map;}
    const NodeMap<int>& processed_map() const {return m_processed_map;}
    const NodeMap<Arc>& pred_map() const {return m_pred_map;}

};

#endif