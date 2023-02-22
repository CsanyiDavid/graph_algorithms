#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

class Node
{
private:
    int m_id;

public:
    int id() const { return m_id; }

    Node(int id = -1)
        : m_id{id}
    {
    }

    friend std::ostream &operator<<(std::ostream &out, Node v);
    friend bool operator==(const Node &v1, const Node &v2) { return v1.id() == v2.id(); }
    friend bool operator!=(const Node &v1, const Node &v2) { return !(v1 == v2); }
    friend bool operator<(const Node& v1, const Node& v2) {return v1.id()<v2.id();}
};

class Arc
{
private:
    int m_id;

public:
    int id() const { return m_id; }

    Arc(int id = -1)
        : m_id{id}
    {
    }

    friend std::ostream &operator<<(std::ostream &out, Arc e);
    friend bool operator==(const Arc &v1, const Arc &v2) { return v1.id() == v2.id(); }
    friend bool operator!=(const Arc &v1, const Arc &v2) { return !(v1 == v2); }
};

class ListDigraph
{
public:
    template <typename INNER, typename OUTER>
    friend class Iterator;

    friend class NodeIt;
    friend class OutArcIt;
    friend class InArcIt;
    friend class AdjArcIt;
    friend class ArcIt;

    ListDigraph()
        : m_next_node_id{0}
        , m_next_arc_id{0}
        , m_node_count{0}
        , m_arc_count{0}
        , m_first_node_ptr{NULL}
        , m_first_arc_ptr{NULL}
        , m_nodes{0}
        , m_arcs{0}
    {}

    ~ListDigraph();

    ListDigraph(const ListDigraph &v) = delete;
    ListDigraph &operator=(const ListDigraph &v) = delete;

    Node add_node();
    Arc add_arc(Node source, Node target);

    int node_count() const { return m_node_count; }
    int arc_count() const { return m_arc_count; }

    int max_node_id() const {return m_next_node_id-1;}
    int max_arc_id() const {return m_next_arc_id-1;}

    friend std::ostream &operator<<(std::ostream &out, const ListDigraph &g);
    friend std::istream &operator>>(std::istream &in, ListDigraph &g);

    bool is_valid(Node v) const;
    bool is_valid(Arc e) const;

    Node source(Arc e) const;
    Node target(Arc e) const;

    int out_degree(Node v) const;
    int in_degree(Node v) const;
    int degree(Node v) const {return in_degree(v) + out_degree(v);}

    void erase(Node node);
    void erase(Arc arc);
    void clear();
    void contract(Arc e);

protected:
    class InnerNode;
    class InnerArc;

    int m_next_node_id;
    int m_next_arc_id;
    int m_node_count;
    int m_arc_count;
    InnerNode *m_first_node_ptr;
    InnerArc *m_first_arc_ptr;
    std::vector<InnerNode *> m_nodes;
    std::vector<InnerArc *> m_arcs;

    InnerNode &get_inner(Node v);
    InnerArc &get_inner(Arc e);
    const InnerNode &get_inner(Node v) const;
    const InnerArc &get_inner(Arc e) const;

    Node get_outer(const InnerNode *v) const;
    Arc get_outer(const InnerArc *e) const;
};

class ListDigraph::InnerNode
{
private:
    int m_id;
    InnerNode *m_prev;
    InnerNode *m_next;
    InnerArc *m_first_out_arc_ptr;
    InnerArc *m_first_in_arc_ptr;
    int m_out_degree;
    int m_in_degree;

    InnerNode(int id)
        : m_id{id}
        , m_prev{NULL}
        , m_next{NULL}
        , m_first_out_arc_ptr{NULL}
        , m_first_in_arc_ptr{NULL}
        , m_out_degree{0}
        , m_in_degree{0}
    {
    }

public:
    InnerNode(const InnerNode &v) = delete;

    InnerNode &operator=(const Node &v) = delete;

    int id() const { return m_id; }

    int out_degree() const { return m_out_degree; }

    int in_degree() const { return m_in_degree; }

    friend class ListDigraph;
    friend class NodeIt;
    friend class OutArcIt;
    friend class InArcIt;
    friend class AdjArcIt;
    friend class ArcIt;
};

class ListDigraph::InnerArc
{
private:
    int m_id;
    InnerNode &m_source;
    InnerNode &m_target;

    InnerArc *m_prev_out; // points to the previous arc in m_source's out arc list
    InnerArc *m_next_out; // points to the next arc in m_source's out arc list
    InnerArc *m_prev_in;  // points to the previous arc in m_target's in arc list
    InnerArc *m_next_in;  // points to the next arc in m_target's in arc list
    InnerArc *m_prev;
    InnerArc *m_next;

    InnerArc(InnerNode &s, InnerNode &t, int id)
        : m_id{id}
        , m_source{s}
        , m_target{t}
        , m_prev_out{NULL}
        , m_next_out{NULL}
        , m_prev_in{NULL}
        , m_next_in{NULL}
        , m_prev{NULL}
        , m_next{NULL}
    {
    }

public:
    int id() const { return m_id; }

    InnerArc(const InnerArc &e) = delete;

    InnerArc &operator=(const InnerArc &v) = delete;

    InnerNode &source() { return m_source; }

    InnerNode &target() { return m_target; }

    const InnerNode &source() const { return m_source; }

    const InnerNode &target() const { return m_target; }

    friend class ListDigraph;
    friend class OutArcIt;
    friend class InArcIt;
    friend class AdjArcIt;
    friend class ArcIt;
};

/*
    abstract base class for a general iterator on a linked list
    define constructor and operator++(int) and
    override operator++ for a child class
*/
template <typename INNER, typename OUTER>
class Iterator
{
protected:
    INNER *m_ptr;
    OUTER m_item;
    const ListDigraph &m_g;

public:
    Iterator(INNER *ptr, const ListDigraph &g)
        : m_ptr(ptr)
        , m_item{g.get_outer(ptr)}
        , m_g{g}
    {
    }

    Iterator(const Iterator &it) = default;

    virtual Iterator &operator++() = 0;

    // virtual Iterator operator++(int) = 0;

    OUTER operator*() const
    {
        if (is_valid())
        {
            return m_item;
        }
        else
        {
            throw "Invalid iterator";
        }
    }

    const OUTER *operator->() const
    {
        if (is_valid())
        {
            return &m_item;
        }
        else
        {
            throw "Invalid iterator!";
        }
    }

    Iterator &operator=(Iterator &it) = default;

    bool is_valid() const { return m_ptr; }
};

class NodeIt : public Iterator<ListDigraph::InnerNode, Node>
{
public:
    NodeIt(const ListDigraph &g)
        : Iterator{g.m_first_node_ptr, g}
    {
    }

    NodeIt &operator++() override;

    NodeIt operator++(int);
};

class OutArcIt : public Iterator<ListDigraph::InnerArc, Arc>
{
public:
    OutArcIt(const ListDigraph &g, Node v)
        : Iterator{g.get_inner(v).m_first_out_arc_ptr, g}
    {
    }

    OutArcIt &operator++() override;

    OutArcIt operator++(int);
};

class InArcIt : public Iterator<ListDigraph::InnerArc, Arc>
{
public:
    InArcIt(const ListDigraph &g, Node v)
        : Iterator{g.get_inner(v).m_first_in_arc_ptr, g}
    {
    }

    InArcIt &operator++() override;

    InArcIt operator++(int);
};

class AdjArcIt : public Iterator<ListDigraph::InnerArc, Arc>
{
private:
    Node m_v;
    bool m_second_phase; //iterate InArcs
public:
    AdjArcIt(const ListDigraph& g, Node v)
        : Iterator{g.get_inner(v).m_first_out_arc_ptr, g}
        , m_v{v}
        , m_second_phase{false}
    {
    }

    AdjArcIt &operator++() override;

    AdjArcIt operator++(int);
};

class ArcIt : public Iterator<ListDigraph::InnerArc, Arc>
{
public:
    ArcIt(const ListDigraph &g)
        : Iterator{g.m_first_arc_ptr, g}
    {
    }

    ArcIt &operator++() override;

    ArcIt operator++(int);
};

//KEY should be Node or Arc
template <typename KEY, typename T>
class MapBase
{
protected:
    const ListDigraph &m_g;
    std::vector<T> m_map;
    T m_fill_value;

public:
    MapBase(const ListDigraph &g, T fill_value = T())
        : m_g{g}
        , m_fill_value{fill_value}
    {}

    T &operator[](KEY k)
    {
        if (m_g.is_valid(k))
        {
            if(k.id()>=m_map.size()){
                m_map.resize(k.id()+1, m_fill_value);
            }
            return m_map[k.id()];
        }
        else
        {
            throw "Invalid key!";
        }
    }

    const T &operator[](KEY k) const
    {
        if (m_g.is_valid(k))
        {
            if(k.id()>=m_map.size()){
                return m_fill_value;
            }
            return m_map[k.id()];
        }
        else
        {
            throw "Invalid Node!";
        }
    }

    virtual void reinitialize(T fill_value = T()) = 0;
};

template <typename T>
class NodeMap : public MapBase<Node, T>
{
public:
    NodeMap(ListDigraph &g, T fill_value = T())
        : MapBase<Node, T>(g, fill_value)
    {
        this->m_map.resize(g.max_node_id(), fill_value);
    }

    friend std::ostream &operator<<(std::ostream &out, const NodeMap &nm)
    {
        out << "NodeMap:" << std::endl;
        for (NodeIt it(nm.m_g); it.is_valid(); ++it)
        {
            out << *it << ' ' << nm[*it] << std::endl;
        }
        return out;
    }

    void reinitialize(T fill_value = T()) override
    {
        for (NodeIt it(this->m_g); it.is_valid(); ++it)
        {
            (*this)[*it] = fill_value;
        }
    }
};

template <typename T>
class ArcMap : public MapBase<Arc, T>
{
public:
    ArcMap(ListDigraph &g, T fill_value = T())
        : MapBase<Arc, T>(g, fill_value)
    {
       this->m_map.resize(g.max_arc_id(), fill_value);
    }

    friend std::ostream &operator<<(std::ostream &out, const ArcMap &am)
    {
        out << "ArcMap:" << std::endl;
        for (ArcIt it(am.m_g); it.is_valid(); ++it)
        {
            out << *it << ' ' << am[*it] << std::endl;
        }
        return out;
    }

    void reinitialize(T fill_value = T()) override
    {
        for (ArcIt it(this->m_g); it.is_valid(); ++it)
        {
            (*this)[*it] = fill_value;
        }
    }
};

#endif