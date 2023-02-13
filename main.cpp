#include<iostream>
#include "graph.h"

using namespace std;

int main(){
    ListDigraph g;
    NodeMap<string> node_names{g};
    ArcMap<int> c{g};
    Node v0 = g.add_node();
    Node v1 = g.add_node();
    Node v2 = g.add_node();
    cout << v0.id() << endl;
    node_names[v0] = "v0";
    cout << v1.id() << endl;
    cout << v2.id() << endl;
    node_names[v1] = "v1";
    node_names[v2] = "v2";
    cout << g.node_count() << endl << endl;
    
    g.add_arc(v1, v2);
    g.add_arc(v1, v0);
    g.add_arc(v0, v2);

    NodeIt it(g);
    NodeIt it_2 = it;
    while(it.is_valid()){
        cout << it->id() << endl;
        ++it;
    }

    cout << g << endl;

    cout << g.is_valid(Node(3));
    cout << g.is_valid(Node(2));
    cout << g.is_valid(Node(-1));
    cout << endl;
    cout << node_names[v0] << ' ';
    cout << node_names[v1] << ' ';
    cout << node_names[v2] << ' ';
    cout << endl;
    
    g.erase(v1);

    cout << g << endl;
    g.erase(Arc(2));
    g.erase(Node(2));

    cout << g << endl;
    cout << g.is_valid(Node(0));
    cout << g.is_valid(Node(1));
    cout << g.is_valid(Arc(2));
    return 0;
}