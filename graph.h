#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<vector>

class ListDigraph;

class Node{
private:
    int m_id;
public:
    int id() const {return m_id;}

    Node(int id)
        : m_id{id}
    {}

    friend std::ostream& operator<<(std::ostream& out, Node v);
};

class Arc{
private:
    int m_id;
public:
    int id() const {return m_id;}

    Arc(int id)
        : m_id{id}
    {}

    friend std::ostream& operator<<(std::ostream& out, Arc e);
};

class ListDigraph{
public:
    friend class NodeIt;
    friend class OutArcIt;
    friend class InArcIt;
    friend class ArcIt;

    template<typename T>
    class NodeMap;

    ListDigraph()
        : m_next_node_id{0}
        , m_next_arc_id{0}
        , m_node_count{0}
        , m_arc_count{0}
        , m_first_node_ptr{NULL}
        , m_first_arc_ptr{NULL}
        , nodes{0}
        , arcs{0}
    {}

    ~ListDigraph();

    ListDigraph(const ListDigraph& v) = delete;

    ListDigraph& operator=(const ListDigraph& v) = delete;

    Node add_node();

    Arc add_arc(Node source, Node target);

    int node_count() const {return m_node_count;}

    int arc_count() const {return m_arc_count;}

    friend std::ostream& operator<<(std::ostream& out, const ListDigraph& g);

    //bool is_valid(const Node& v) const {return nodes[v->id()]};

    //bool is_valid(const Arc& e) const {return nodes[e->id()]};

private:
    class RealNode;
    class RealArc;

    int m_next_node_id;
    int m_next_arc_id;
    int m_node_count;
    int m_arc_count;
    RealNode* m_first_node_ptr;
    RealArc* m_first_arc_ptr;
    std::vector<RealNode*> nodes;
    std::vector<RealArc*> arcs;

    RealNode& get_inner(Node v){return *nodes[v.id()];}
    RealArc& get_inner(Arc e){return *arcs[e.id()];}
    const RealNode& get_inner(Node v) const {return *nodes[v.id()];}
    const RealArc& get_inner(Arc e) const {return *arcs[e.id()];}
};

class ListDigraph::RealNode{
private:
    int m_id;
    RealNode* m_prev;
    RealNode* m_next;
    RealArc* m_first_out_arc_ptr;
    RealArc* m_first_in_arc_ptr;
    int m_out_degree;
    int m_in_degree;

    RealNode(int id)
        : m_id{id}
        , m_prev{NULL}
        , m_next{NULL}
        , m_first_out_arc_ptr{NULL}
        , m_first_in_arc_ptr{NULL}
        , m_out_degree{0}
        , m_in_degree{0}
    {}

public:

    RealNode(const RealNode& v) = delete;

    RealNode& operator=(const Node& v) = delete;

    int id() const {return m_id;}

    int out_degree() const {return m_out_degree;}

    int in_degree() const {return m_in_degree;}

    friend class ListDigraph;
    friend class NodeIt;
    friend class OutArcIt;
    friend class InArcIt;
    friend class ArcIt;
};

class ListDigraph::RealArc{
private:
    int m_id;
    RealNode& m_source;
    RealNode& m_target;

    RealArc* m_prev_out; //points to the previous arc in m_source's out arc list
    RealArc* m_next_out; //points to the next arc in m_source's out arc list
    RealArc* m_prev_in; //points to the previous arc in m_target's in arc list
    RealArc* m_next_in; //points to the next arc in m_target's in arc list
    RealArc* m_prev;
    RealArc* m_next;

    RealArc(RealNode& s, RealNode& t, int id)
        : m_id{id}
        , m_source{s}
        , m_target{t}
        , m_prev_out{NULL}
        , m_next_out{NULL}
        , m_prev_in{NULL}
        , m_next_in{NULL}
    {}

public:

    int id() const {return m_id;}

    RealArc(const RealArc& e) = delete;

    RealArc& operator=(const RealArc& v) = delete;

    RealNode& source() {return m_source;}

    RealNode& target() {return m_target;}

    const RealNode& source() const {return m_source;}

    const RealNode& target() const {return m_target;}

    friend class ListDigraph;
    friend class OutArcIt;
    friend class InArcIt;
    friend class ArcIt;
};

/*
    abstract base class for a general iterator on a linked list
    define constructor and operator++(int) and
    override operator++ for a child class
*/
template<typename T>
class Iterator{
protected:
    T m_item;
    const ListDigraph& m_g;
public:
    Iterator(T item, const ListDigraph& g)
        : m_item{item}
        , m_g{g}
    {}

    Iterator(const Iterator& it) = default;

    virtual Iterator& operator++() = 0;

    //virtual Iterator operator++(int) = 0;

    T operator*() const {
        if(is_valid()){
            return m_item;
        } else {
            throw "Invalid iterator";
        }
    }

    T* operator->(){
        if(is_valid()){
            return &m_item;
        } else {
            throw "Invalid iterator!";
        }
    }

    const T* operator->() const{
        if(is_valid()){
            return &m_item;
        } else {
            throw "Invalid iterator!";
        }
    }

    Iterator& operator=(Iterator& it) = default;

    bool is_valid() const {return m_item.id()>=0;}
};

class NodeIt : public Iterator<Node>{
public:
    NodeIt(const ListDigraph& g)
        : Iterator{
            g.m_first_node_ptr ? Node{g.m_first_node_ptr->id()} : Node{-1}
            , g
          }
    {}

    NodeIt& operator++() override;

    NodeIt operator++(int);
};

class OutArcIt : public Iterator<Arc>{
public:
    OutArcIt(Node v, const ListDigraph& g)
        : Iterator{
            g.get_inner(v).m_first_out_arc_ptr ? Arc{g.get_inner(v).m_first_out_arc_ptr->id()} : Arc{-1}
            , g
          }
    {}

    OutArcIt& operator++() override;

    OutArcIt operator++(int);
};

class InArcIt : public Iterator<Arc>{
public:
    InArcIt(Node v, const ListDigraph& g)
        : Iterator{
            g.get_inner(v).m_first_in_arc_ptr ? Arc(g.get_inner(v).m_first_in_arc_ptr->id()) : Arc{-1}
            , g
          }
    {}

    InArcIt& operator++() override;

    InArcIt operator++(int);
};

class ArcIt : public Iterator<Arc>{
private:
    Node m_node;
public:
    ArcIt(const ListDigraph& g)
        : m_node{Node(g.m_first_node_ptr->id())}
        , Iterator{
            g.m_first_arc_ptr ? Arc(g.m_first_arc_ptr->id()) : Arc{-1}
            , g
          }
    {}

    ArcIt& operator++() override;

    ArcIt operator++(int);
};

/*template<typename T>
class ListDigraph::NodeMap{
private:
    const ListDigraph& m_g;
    std::vector<T> m_map;
public:
    NodeMap(const ListDigraph& g)
        : m_g{g}
        , m_map{g.m_next_node_id-1, 0}
    {}

    T& operator[](Node& v){
        return m_map[v.id()];
    }
};*/

#endif