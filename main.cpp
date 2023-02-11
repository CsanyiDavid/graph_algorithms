#include<iostream>
#include "graph.h"

using namespace std;

int main(){
    ListDigraph g;
    ListDigraph::Node& v0 = g.add_node();
    ListDigraph::Node& v1 = g.add_node();
    ListDigraph::Node& v2 = g.add_node();
    cout << v0.id() << endl;
    cout << v1.id() << endl;
    cout << v2.id() << endl;
    cout << g.node_count() << endl << endl;
    
    g.add_arc(v1, v2);

    ListDigraph::NodeIt it(g);
    ListDigraph::NodeIt it_2 = it;
    while(it.is_valid()){
        cout << it->id() << endl;
        ++it;
    }

    cout << g << endl;

    return 0;
}