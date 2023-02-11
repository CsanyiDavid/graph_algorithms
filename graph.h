#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>

class ListDigraph{
public:
    class Node;
    class NodeIt;
    class Arc;
    class OutArcIt;
    class InArcIt;
    class ArcIt;

    ListDigraph()
        : m_next_node_id{0}
        , m_next_arc_id{0}
        , m_node_count{0}
        , m_arc_count{0}
        , m_first_node_ptr{NULL}
    {}

    ~ListDigraph();

    ListDigraph(const ListDigraph& v) = delete;

    ListDigraph& operator=(const ListDigraph& v) = delete;

    Node& add_node();

    Arc& add_arc(Node& s, Node& t);

    int node_count() const {return m_node_count;}

    int arc_count() const {return m_arc_count;}

    friend std::ostream& operator<<(std::ostream& out, const ListDigraph& g);

private:
    int m_next_node_id;
    int m_next_arc_id;
    int m_node_count;
    int m_arc_count;
    Node* m_first_node_ptr;
};

class ListDigraph::Node{
private:
    int m_id;
    Node* m_prev;
    Node* m_next;
    Arc* m_first_out_arc_ptr;
    Arc* m_first_in_arc_ptr;
    int out_degree;
    int in_degree;

    Node(int id)
        : m_id{id}
        , m_prev{NULL}
        , m_next{NULL}
        , m_first_out_arc_ptr{NULL}
        , m_first_in_arc_ptr{NULL}
        , out_degree{0}
        , in_degree{0}
    {}

public:

    Node(const Node& v) = delete;

    Node& operator=(const Node& v) = delete;

    int id() const {return m_id;}

    friend class ListDigraph;

    friend std::ostream& operator<<(std::ostream& out, const Node& v);
};

class ListDigraph::Arc{
private:
    Node& m_source;
    Node& m_target;

    Arc* m_prev_out; //points to the previous arc in m_source's out arc list
    Arc* m_next_out; //points to the next arc in m_source's out arc list
    Arc* m_prev_in; //points to the previous arc in m_target's in arc list
    Arc* m_next_in; //points to the next arc in m_target's in arc list

public:
    Arc(Node& s, Node& t)
        : m_source{s}
        , m_target{t}
        , m_prev_out{NULL}
        , m_next_out{NULL}
        , m_prev_in{NULL}
        , m_next_in{NULL}
    {}

    Arc(const Arc& e) = delete;

    Arc& operator=(const Arc& v) = delete;

    Node& source() {return m_source;}

    Node& target() {return m_target;}

    friend class ListDigraph;
};

/*
    abstract base class for a general iterator on a linked list
    define constructor and operator++(int) and
    override operator++ for a child class
*/
template<typename T>
class Iterator{
protected:
    T* m_ptr;
public:
    Iterator(T* ptr)
        : m_ptr{ptr}
    {}

    Iterator(const Iterator& it) = default;

    virtual Iterator& operator++() = 0;

    //virtual Iterator operator++(int) = 0;

    T& operator*(){
        if(is_valid()){
            return *m_ptr;
        } else {
            throw "Invalid iterator";
        }
    }

    T* operator->(){
        if(is_valid()){
            return m_ptr;
        } else {
            throw "Invalid iterator!";
        }
    }

    Iterator& operator=(Iterator& v_it) = default;

    bool is_valid() const {return m_ptr != NULL;}

    friend class ListDigraph;
};

class ListDigraph::NodeIt : public Iterator<ListDigraph::Node>{
public:
    NodeIt(const ListDigraph& g)
        : Iterator{g.m_first_node_ptr}
    {}

    NodeIt& operator++() override;

    NodeIt operator++(int);
};

class ListDigraph::OutArcIt : public Iterator<ListDigraph::Arc>{
public:
    OutArcIt(const Node& v)
        : Iterator{v.m_first_out_arc_ptr}
    {}

    OutArcIt& operator++() override;

    OutArcIt operator++(int);
};

class ListDigraph::InArcIt : public Iterator<ListDigraph::Arc>{
public:
    InArcIt(const Node& v)
        : Iterator{v.m_first_in_arc_ptr}
    {}

    InArcIt& operator++() override;

    InArcIt operator++(int);
};

#endif