#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

class Dijkstra{
private:
    ListDigraph& m_g;
    const ArcMap<double>& m_c;
    Node m_s;
    NodeMap<double> m_dist_map;
    NodeMap<Arc> m_pred_map;
    NodeMap<int> m_processed_map;
    NodeMap<int> m_reached_map;

public:
    Dijkstra(ListDigraph& g, const ArcMap<double>& c, Node s)
        : m_g{g}
        , m_c{c}
        , m_s{s}
        , m_dist_map{g, -1}
        , m_pred_map{g, Arc(-1)}
        , m_processed_map{g, 0}
        , m_reached_map{g, 0}
    {}
    
    void clear();

    void run();

    void set_source(Node s) {m_s = s;}

    const NodeMap<double>& dist_map() const {return m_dist_map;}
    const NodeMap<int>& reached_map() const {return m_reached_map;}
    const NodeMap<Arc>& pred_map() const {return m_pred_map;}
};

#endif