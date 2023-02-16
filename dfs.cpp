#include "graph.h"
#include "dfs.h"


//DFSIterator

void DFSIterator::run(Node u){
    for(OutArcIt it(m_g, u); it.is_valid(); ++it){
        Node v{m_g.target(*it)};
        if(!m_reached_map[v]){
            m_reached_map[v] =true;
            m_pred_map[v] = *it;
            m_next_node_map[m_prev_node] = v;
            m_prev_node = v;
            run(v);
        }
    }

}


DFSIterator& DFSIterator::operator++(){
    if(is_valid()){
        m_current_node = m_next_node_map[m_current_node];
    }
    return *this;
}

DFSIterator DFSIterator::operator++(int){
    DFSIterator temp{*this};
    ++(*this);
    return temp;
}

Arc DFSIterator::get_pred_arc() const{
    return m_pred_map[m_current_node];
}