#define CATCH_CONFIG_MAIN

#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<string>
#include<vector>

#include "catch.hpp"
#include "../graph.h"
#include "../heap.h"


//TEST GRAPH

TEST_CASE("add nodes, arcs and count them", "[graph]"){
    srand(time(NULL));
    for(int sub_test_case=0; sub_test_case<10; ++sub_test_case){
        ListDigraph g;
        int n = rand()%1000;
        int m = rand()%1000;
        for(int i=0; i<n; ++i){
            g.add_node();
        }
        for(int i=0; i<m; ++i){
            Node u{rand()%n};
            Node v{rand()%n};
            g.add_arc(u, v);
        }
        CHECK(g.node_count()==n);
        CHECK(g.arc_count()==m);
    }
}

TEST_CASE("erase arcs and is_valid arc", "[graph]"){
    ListDigraph g;
    srand(time(NULL));
    for(int sub_test_case=0; sub_test_case<10; ++sub_test_case){
        ListDigraph g;
        std::vector<int> node_ids;
        std::vector<int> arc_ids;
        int n = 0;
        int m = 0;
        for(int iteration=0; iteration<3; ++iteration){
            int new_node_cnt = rand()%100 + 1;
            int new_arc_cnt = rand()%100;
            n += new_node_cnt;
            m += new_arc_cnt;
            for(int i=0; i<new_node_cnt; ++i){
                node_ids.push_back(g.add_node().id());
            }
            for(int i=0; i<new_arc_cnt; ++i){
                Node u{rand()%n};
                Node v{rand()%n};
                arc_ids.push_back(g.add_arc(u, v).id());
            }
            CHECK(g.arc_count()==m);
            int arcs_to_delete_cnt = m>0 ? rand()%m : 0;
            for(int i=0; i<arcs_to_delete_cnt; ++i){
                int r = rand()%arc_ids.size();
                int id = arc_ids[r];
                g.erase(Arc(id));
                arc_ids[r] = arc_ids[arc_ids.size()-1];
                arc_ids.resize(arc_ids.size()-1);
                CHECK_FALSE(g.is_valid(Arc(id)));
            }
            m -= arcs_to_delete_cnt;
            CHECK(g.arc_count()==m);
            CHECK(g.node_count()==n);
            for(int i=0; i<arc_ids.size(); ++i){
                CHECK(g.is_valid(Arc(arc_ids[i])));
            }
        }
    }
}

TEST_CASE("source and target", "[graph]"){
    ListDigraph g;
    int n = rand()%1000 + 1;
    int m = rand()%1000 + 1;
    for(int i=0; i<n; ++i){
        g.add_node();
    }
    std::vector<Node> sources;
    std::vector<Node> targets;
    for(int i=0; i<m; ++i){
        Node u{rand()%n};
        Node v{rand()%n};
        g.add_arc(u, v);
        sources.push_back(u);
        targets.push_back(v);
    }
    srand(time(NULL));
    for(int i=0; i<100; ++i){
        int r = rand() % m;
        CHECK(g.target(Arc(r))==targets[r]);
        CHECK(g.source(Arc(r))==sources[r]);
    }
}

TEST_CASE("degrees, erase node", "[graph]"){
    ListDigraph g;
    for(int i=0; i<20; ++i){
        g.add_node();
    }
    g.add_arc(Node(0), Node(1)); //0
    g.add_arc(Node(0), Node(1)); //1
    g.add_arc(Node(0), Node(2)); //2
    g.add_arc(Node(0), Node(6)); //3
    g.add_arc(Node(0), Node(12)); //4
    g.add_arc(Node(1), Node(0)); //5
    g.add_arc(Node(1), Node(12)); //6
    g.add_arc(Node(12), Node(7)); //7
    g.add_arc(Node(12), Node(6)); //8
    g.add_arc(Node(4), Node(1)); //9
    CHECK(g.degree(0)==6); 
    CHECK(g.degree(1)==5);
    CHECK(g.out_degree(0)==5);
    CHECK(g.out_degree(12)==2);
    CHECK(g.out_degree(2)==0);
    CHECK(g.in_degree(0)==1);
    CHECK(g.in_degree(12)==2);
    g.erase(Arc(4));
    g.erase(Arc(3));
    CHECK(g.out_degree(0)==3);
    CHECK(g.in_degree(12)==1);
    g.erase(Node(12));
    g.erase(Node(0));
    CHECK(g.out_degree(1)==0);
    CHECK(g.node_count()==18);
}

TEST_CASE("node iterator", "[graph]"){
    ListDigraph g;
    std::set<int> node_ids;
    srand(time(NULL));
    for(int iteration=0; iteration<5; ++iteration){
        int new_node_cnt = rand()%1000;
        for(int i=0; i<new_node_cnt; ++i){
            node_ids.insert(g.add_node().id());    
        }
        int erase_cnt = rand()%g.node_count()-10;
        for(int i=0; i<erase_cnt; ++i){
            int r = rand()%g.node_count();
            if(g.is_valid(Node(r))){
                g.erase(Node(r));
                node_ids.erase(r);
            }
        }
        std::set<int> iterator_output;
        for(NodeIt it(g); it.is_valid(); ++it){
            int id= it->id();
            iterator_output.insert(id);
        }
        CHECK(node_ids == iterator_output);
    }
}

TEST_CASE("arc iterators", "[graph]"){
    ListDigraph g;
    for(int i=0; i<100; ++i){
        g.add_node();
    }
}

//TEST BFS

//TEST DFS

//TEST HEAP

TEST_CASE("insert, delete and size", "[heap]"){
    BinaryHeap<int, int> h;
    h.insert(1, 1);
    CHECK(h.size() == 1);
    h.insert(1, 1);
    CHECK(h.size() == 2);
    h.insert(1, 1);
    CHECK(h.size() == 3);
    h.insert(1, 1);
    CHECK(h.size() == 4);
    h.insert(1, 1);
    CHECK(h.size() == 5);
    h.del_min();
    CHECK(h.size() == 4);
    h.del_min();
    CHECK(h.size() == 3);
    h.insert(1, 1);
    CHECK(h.size() == 4);

}

TEST_CASE("empty and delete from empty", "[heap]"){
    BinaryHeap<double, std::string> h;
    CHECK(h.empty());
    CHECK_THROWS(h.del_min());
    h.insert(1.2, "a");
    CHECK_FALSE(h.empty());
    h.del_min();
    CHECK_THROWS(h.del_min());
    CHECK(h.empty());
    CHECK_THROWS(h.del_min());
}

TEST_CASE("sort", "[heap]"){
    for(int sub_test_case=0; sub_test_case<10; ++sub_test_case){
        srand(time(NULL));
        std::vector<int> random_numbers;
        BinaryHeap<int, int> h;
        for(int i=0;i<100; ++i){
            int r = rand()%1000;
            random_numbers.push_back(r);
            h.insert(r, r);
        }
        std::vector<int> heap_outputs;
        for(int i=0; i<100; ++i){
            heap_outputs.push_back(h.del_min());
        }
        std::sort(random_numbers.begin(), random_numbers.end());
        CHECK(random_numbers == heap_outputs);
    }
}

TEST_CASE("decrease key", "[heap]"){
    for(int sub_test_case=0; sub_test_case<10; ++sub_test_case){
        srand(time(NULL));
        BinaryHeap<int, int> h;
        h.insert(2000, 2000);
        for(int i=0; i<10; ++i){
            int r = rand()%1000;
            if(r!=500){
                h.insert(r, r);
            }
        }
        h.decrease_key(2000, 1500);
        std::vector<int> outputs;
        while(!h.empty()){
            outputs.push_back(h.del_min());
            if(outputs[outputs.size()-1]==2000){
                outputs[outputs.size()-1]=500;
            }
        }
        CHECK(std::is_sorted(outputs.begin(), outputs.end()));
    }
}

//TEST DIJKSTRA