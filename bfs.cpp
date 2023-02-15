#include "graph.h"
#include "bfs.h"
#include <queue>


//BFSIterator


BFSIterator& BFSIterator::operator++(){
    if(is_valid()){
        m_current_node = q.front();
        q.pop();
        for(OutArcIt it(m_current_node, m_g); it.is_valid(); ++it){
            Node v{m_g.target(*it)};
            if(!m_reached_map[v]){
                m_reached_map[v] = true;
                m_pred_map[v] = *it;
                q.push(v);
            }
        }
    }
    return *this;
}

BFSIterator BFSIterator::operator++(int){
    BFSIterator temp{*this};
    ++(*this);
    return temp;
}

Arc BFSIterator::get_pred_arc() const{
    return m_pred_map[m_current_node];
}


//BFS

void BFS::clear(){
    m_dist_map.reinitialize(-1);
    m_pred_map.reinitialize(Arc(-1));
    m_reached_map.reinitialize(0);
}


void BFS::run(){
    clear();
    std::queue<Node> q;
    q.push(m_s);
    m_reached_map[m_s] = true;
    m_dist_map[m_s] = 0;
    for(BFSIterator it(m_g, m_s); it.is_valid(); ++it){
        Node current_node{*it};
        m_reached_map[current_node] = true;
        Arc e{it.get_pred_arc()};
        if(current_node != m_s){
            Node pred_node(m_g.source(e));
            m_dist_map[current_node] = m_dist_map[pred_node] + 1;
            m_pred_map[current_node] = e;
        }
    }
}