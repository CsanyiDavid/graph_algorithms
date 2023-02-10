#include<iostream>
#include<list>
#include "graph.h"

using namespace std;

int main(){
    ListDigraph g;
    ListDigraph::Node v0 = g.add_node();
    ListDigraph::Node v1 = g.add_node();
    ListDigraph::Node v2 = g.add_node();
    cout << v0.get_id() << endl;
    cout << v1.get_id() << endl;
    cout << v2.get_id() << endl;
    cout << g.node_count() << endl << endl;
    
    ListDigraph::NodeIt it(g);
    while(it.is_valid()){
        cout << it->get_id() << endl;
        ++it;
    }
    return 0;
}