#define CATCH_CONFIG_MAIN

#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<string>
#include<vector>

#include "catch.hpp"
#include "../heap.h"


//TEST GRAPH

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