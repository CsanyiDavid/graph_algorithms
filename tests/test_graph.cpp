#include "graph.h"
#include "test_graph.h"
#include <iostream>
#include <cassert>

/*
Functions to test:
ListDiraph
add_node
add_arc
node_count
arc_count
operator<<
is_valid
source
target
out_degree
in_degree
erase

NodeIt, ArcIt, OutArcIt, InArcIt
constructur
operator++
operator++(int)

NodeMap, ArcMap
constructor
operator[]
operator[] const
*/

void run_graph_tests(){
    test();
}

bool test(){
    ListDigraph g{};
    NodeMap<std::string> nm{g};
    ArcMap<int> am{g};
    std::vector<Node> nodes;
    std::vector<std::string> node_names{"0","1","2","3","4","5","6","7","8","9"};
    for(int i=0; i<10; ++i){
        nodes.push_back(g.add_node());
        nm[nodes[i]] = node_names[i];
    }
    nm[nodes[3]] = "third node";
    std::cout << g << std::endl;
    std::vector<Arc> arcs;
    arcs.push_back(g.add_arc(nodes[1], nodes[2]));
    arcs.push_back(g.add_arc(nodes[1], nodes[3]));
    arcs.push_back(g.add_arc(nodes[1], nodes[4]));
    arcs.push_back(g.add_arc(nodes[5], nodes[6]));
    arcs.push_back(g.add_arc(nodes[6], nodes[5]));
    arcs.push_back(g.add_arc(nodes[1], nodes[2]));
    arcs.push_back(g.add_arc(nodes[9], nodes[9]));
    am[arcs[3]] = 123;
    std::cout << g << std::endl;
    assert(g.node_count()==10);
    assert(g.arc_count()==7);
    std::vector<int> expected_out_degrees{0,4,0,0,0,1,1,0,0,1};
    std::vector<int> expected_in_degrees{0,0,2,1,1,1,1,0,0,1};
    for(int i=0; i<10; ++i){
        assert(g.out_degree(nodes[i])==expected_out_degrees[i]);
        assert(g.in_degree(nodes[i])==expected_in_degrees[i]);
    }
    assert(g.source(arcs[0]).id()==1);
    assert(g.target(arcs[0]).id()==2);
    assert(g.source(arcs[6]).id()==9);
    assert(g.target(arcs[6]).id()==9);
    g.erase(nodes[1]);
    g.erase(arcs[6]);
    std::cout << g << std::endl;

    std::cout << nm << std::endl;
    std::cout << am << std::endl;
    //am[arcs[2]];
    assert(!g.is_valid(arcs[1]));
    assert(g.is_valid(arcs[4]));
    assert(!g.is_valid(nodes[1]));
    assert(g.is_valid(nodes[0]));
    return true;
}