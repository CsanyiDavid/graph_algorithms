#include<iostream>
#include "graph.h"
#include "tests/test_graph.h"
#include "bfs.h"
#include "dfs.h"

using namespace std;

int main(){
    ListDigraph g;
    cin >> g;
    cout << g;
    for(DFSIterator it{g, Node(0)}; it.is_valid(); ++it){
        cout << (g.is_valid(it.get_pred_arc()) ? g.source(it.get_pred_arc()) : Node(-1)) << ' ' << *it << endl;
    }
}