#include<iostream>
#include "graph.h"
#include "tests/test_graph.h"
#include "bfs.h"
#include "dfs.h"
#include "heap.h"

using namespace std;

int main(){
    BinaryHeap<int, int> h;
    h.insert(2,2);
    h.insert(234,234);
    h.insert(4,4);
    h.insert(4,4);
    h.insert(12,12);
    h.insert(6,6);
    h.insert(-102,-102);
    h.insert(2,2);
    h.insert(10,10);
    h.insert(4,4);
    h.insert(-1,-1);
    h.insert(5,5);
    h.insert(23,23);
    h.insert(67,67);
    h.insert(-11,-11);
    h.insert(222222,222222);
    h.insert(4,4);
    h.insert(40,40);
    h.insert(5,5);
    h.insert(-33,-33);
    h.insert(2,2);
    cout << h << endl;
    h.decrease_key(15, 222222);
    cout << h << endl;
    while(!h.empty()){
        cout << h.del_min() << ' ';
    }
    cout << endl;
    cout << h << endl;
}