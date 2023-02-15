#include "graph.h"
#include "bfs.h"
#include <queue>

void BFS::run(){
    std::queue<Node> q;
    q.push(m_s);
    m_reached_map[m_s] = true;
    m_dist_map[m_s] = 0;
    while(!q.empty()){
        Node current_node = q.front();
        q.pop();
        m_processed_map[current_node] = true;
        for(OutArcIt it(current_node, m_g); it.is_valid(); ++it){
            Node v{m_g.target(*it)};
            if(!m_reached_map[v]){
                m_reached_map[v] = true;
                m_dist_map[v] = m_dist_map[current_node] + 1;
                m_pred_map[v] = *it;
                q.push(v);
                std::cout << current_node << ' ' << v << std::endl;
            }
        }
    }
}