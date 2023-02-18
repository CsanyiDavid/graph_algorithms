#include <iostream>
#include <fstream>
#include "graph.h"
#include "tests/test_graph.h"
#include "bfs.h"
#include "dfs.h"
#include "heap.h"
#include "dijkstra.h"

using namespace std;

int main(){
    ListDigraph g;
    std::ifstream GraphFile("input_graph.txt");
    GraphFile >> g;
    GraphFile.close();
    cout << g << endl;
    ArcMap<double> c(g, 23.0);
    /*Dijkstra d{g, c, Node(0)};
    d.run();
    cout << d.dist_map() << endl;*/
}