#include<iostream>
#include "graph.h"
#include "tests/test_graph.h"
#include "bfs.h"

using namespace std;

int main(){
    ListDigraph g;
    cin >> g;
    cout << g;
    BFS bfs{g, Node(0)};
    bfs.run();
    const NodeMap<int> dist_map{bfs.dist_map()};
    cout << dist_map << endl;
    const NodeMap<int> processed_map{bfs.processed_map()};
    cout << processed_map << endl;
    const NodeMap<int> reached_map{bfs.reached_map()};
    cout << reached_map << endl;
    const NodeMap<Arc> pred_map{bfs.pred_map()};
    for(NodeIt it(g); it.is_valid(); ++it){
        Node pred_node{g.is_valid(pred_map[*it]) ?  g.source(pred_map[*it]) : Node(-1)};
        cout << *it << ' ' << pred_node << endl;
    }
}