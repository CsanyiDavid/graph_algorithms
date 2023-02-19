#include "dijkstra.h"
#include "graph.h"
#include "heap.h"

void Dijkstra::clear(){
    m_dist_map.reinitialize(-1);
    m_pred_map.reinitialize(Arc(-1));
    m_processed_map.reinitialize(0);
    m_reached_map.reinitialize(0);
}

void Dijkstra::run(){
    clear();
    BinaryHeap<double, Node> h;
    h.insert(0, m_s);
    m_reached_map[m_s] = 1;
    m_dist_map[m_s] = 0;
    while(!h.empty()){
        Node v{h.del_min()};
        m_processed_map[v] = 1;
        for(OutArcIt it(m_g, v); it.is_valid(); ++it){
            Node other_node{m_g.target(*it)};
            if(m_processed_map[other_node]){
                //do nothing
            } else if(m_reached_map[other_node]){
                if(m_dist_map[other_node]>m_dist_map[v]+m_c[*it]){
                    double diff = m_dist_map[other_node]-m_dist_map[v]-m_c[*it];
                    m_dist_map[other_node]=m_dist_map[v]+m_c[*it];
                    m_pred_map[other_node] = *it;
                    h.decrease_key(other_node, diff);
                }
            } else { //not visited yet
                m_dist_map[other_node]=m_dist_map[v]+m_c[*it];
                m_pred_map[other_node] = *it;
                m_reached_map[other_node] = 1;
                h.insert(m_dist_map[other_node], other_node);
            }
        }
    }

}