#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "map"
#include "vector"
#include "set"
#include <algorithm>

using std::map;
using std::set;
using std::vector;
using std::pair;

template<typename E, typename V>
class Graph
{

public: 
    Graph(bool _isWeighted = false, bool _isDirected = false);

    void add(V const& _vertex);
    void connect(V const& _from ,V const& _to, E const& _weight = 0);
    void disconnect(V const& _from ,V const& _to);

    bool isNeighbors(V const& _lhs, V const& _rhs) const;
    bool isConnected(V const& _lhs, V const& _rhs) const;

    void primAlgorithem();

private:
    
    class Edge
    {
    public:

        Edge();
        Edge(E const& _weight);
        bool operator <(Edge const& _rhs) const;
        E const& weight() const;
        void weight(E const&);
        bool isInTree() const;
        void setInTree(bool _isInTree);

    private:
        E m_weight;
        bool m_isInMinTree;

    };

    struct CompareSecond
    {
        typedef std::pair<V const*, Edge> MyPairType;
        bool operator()(const MyPairType& left, const MyPairType& right) const;
    };

private:
    typedef typename map<V const*, Edge>::iterator AdjacentsConstIterator;
    bool recursiveSearch(V const& _source, V const& _dest, map<V const*, bool>& _visited) const;
    Edge* findNextMin(set<V>& _connected);
    void initGraph();
    void insertEdges(vector<pair<V const*, Edge*> >& _edges, map<V const*, Edge> _neghibors);


private:
    typedef map<V, map<V const*, Edge> > Adjacents;
    Adjacents m_adjecents;
    bool const m_isWeighted;
    bool const m_isDirected;
   
};


template<typename E, typename V>
void Graph<E, V>::initGraph()
{
    typename Adjacents::iterator itrB = m_adjecents.begin();
    typename Adjacents::iterator itrE = m_adjecents.end();

    typename map<V const*, Edge>::iterator edgeItrB;
    typename map<V const*, Edge>::iterator edgeItrE;

    while(itrB != itrE)
    {
        edgeItrB = itrB->second.begin();
        edgeItrE = itrB->second.end();

        while(edgeItrB!=edgeItrE)
        {
            edgeItrB->second.setInTree(false);
            ++edgeItrB;
        }
        ++itrB;
    }
}


template<typename E, typename V>
typename Graph<E, V>::Edge* Graph<E, V>::findNextMin(set<V>& _connected)
{
    typename set<V>::iterator itrB = _connected.begin();
    typename set<V>::iterator itrE = _connected.end();
    typename set<V>::iterator itrMin;
    
    
    while(itrB!=itrE)
    {
       /*  itrMin = std::min_element(itrB, itrE, CompareEdgesPointers());

        if(!(*itrMin)->isInTree())
        {
            _connected.erase(itrMin);
            break;
        }

        ++itrB; */
    }  

    return 0;
}

template<typename E, typename V>
void Graph<E, V>::insertEdges(vector<pair<V const*, Edge*> >& _edges, map<V const*, Edge> _neghibors)
{
    typename map<V const*, Edge>::iterator itrB = _neghibors.begin();
    typename map<V const*, Edge>::iterator itrE = _neghibors.end();

    while (itrB!=itrE)
    {
        
        _edges.insert(pair<V const*, Edge*>(itrB->first, &itrB->second));
        ++itrB;
    }
    
}

template<typename E, typename V>
void Graph<E, V>::primAlgorithem()
{

    initGraph();

    set<V> connected;

    size_t const size = m_adjecents.size();
    typename Adjacents::iterator itrFirst = m_adjecents.begin();

    connected.insert(itrFirst->first);
   
    for(size_t counter = 0; counter + 1 < size;)
    {
       findNextMin(connected);
       /*  minEdge->setInTree(true);
        itrMin->second.setInTree(true);
        connected.insert(m_adjecents[*itrMin->first]);
        ++itrFirst;   */
    }  

}


template<typename E, typename V>
Graph<E, V>::Graph(bool _isWeighted, bool _isDirected)
: m_isWeighted(_isWeighted)
, m_isDirected(_isDirected)
{

}

template<typename E, typename V>
void Graph<E, V>::add(V const& _vertex)
{
    typename Adjacents::iterator itr = m_adjecents.find(_vertex);
    if(itr == m_adjecents.end())
    {
        m_adjecents[_vertex] = map<V const*,Edge>();
    }
}

template<typename E, typename V>
void Graph<E, V>::connect(V const& _from ,V const& _to, E const& _weight)
{

    if(!m_isWeighted)
    {
        const_cast<E&>(_weight) = 0;
    }

    Graph::Edge newEdge(_weight);
    
    typename Adjacents::iterator itrFrom = m_adjecents.find(_from);
    typename Adjacents::iterator itrTo = m_adjecents.find(_to);

    if(itrFrom != m_adjecents.end() && itrTo != m_adjecents.end())
    {
        m_adjecents[_from][&(itrTo->first)] = newEdge;

        if(!m_isDirected)
        {
            m_adjecents[_to][&(itrFrom->first)] = newEdge;
        }
    }
}

template<typename E, typename V>
void Graph<E, V>::disconnect(V const& _from ,V const& _to)
{
    typename Adjacents::iterator itrFrom = m_adjecents.find(_from);
    typename Adjacents::iterator itrTo = m_adjecents.find(_to);

    if(itrFrom == m_adjecents.end() || itrTo == m_adjecents.end())
    {
        return;
    }

    if(isNeighbors(_from,_to))
    {
        itrFrom->second.erase(itrFrom->second.find(&itrTo->first));

        if(!m_isDirected)
        {
            itrTo->second.erase(itrTo->second.find(&itrFrom->first));
        }
    }
}

template<typename E, typename V>
bool Graph<E, V>::isNeighbors(V const& _lhs, V const& _rhs) const
{
    typename Adjacents::const_iterator itrFrom = m_adjecents.find(_lhs);
    typename Adjacents::const_iterator itrTo = m_adjecents.find(_rhs);

    if(itrFrom == m_adjecents.end() || itrTo == m_adjecents.end())
    {
        return false;
    }

    return itrFrom->second.find(&itrTo->first) != itrFrom->second.end() ? true: false;
    
}

template<typename E, typename V>
bool Graph<E, V>::isConnected(V const& _lhs, V const& _rhs) const
{
    map<V const*, bool> visited;

    typename Adjacents::const_iterator itrB = m_adjecents.begin();
    typename Adjacents::const_iterator itrE = m_adjecents.end();

    while(itrB!=itrE)
    {
        visited[&itrB->first] = false;
        ++itrB;
    }

    return recursiveSearch(_lhs, _rhs, visited);

}

template<typename E, typename V>
bool Graph<E, V>::recursiveSearch(V const& _source, V const& _dest, map<V const*, bool>& _visited) const
{
    if(_source == _dest)
    {
        return true;
    }

    if(_visited[&_source] == true)
    {
        return false;
    }

    _visited[&_source] = true;

    typename Adjacents::const_iterator itrFrom = m_adjecents.find(_source);
    typename map<V const*, Edge>::const_iterator itrB = itrFrom->second.begin();
    typename map<V const*, Edge>::const_iterator itrE = itrFrom->second.end();

    while(itrB != itrE)
    {
        if(recursiveSearch(*(itrB->first),_dest,_visited))
        {
            return true;
        }
        
        ++itrB;
    }

    return false;
}

template<typename E, typename V>
Graph<E, V>::Edge::Edge()
: m_weight()
, m_isInMinTree(false)
{

}

template<typename E, typename V>
Graph<E, V>::Edge::Edge(E const& _weight)
: m_weight(_weight)
, m_isInMinTree(false)
{
    
}

template<typename E, typename V>
E const& Graph<E, V>::Edge::weight() const
{
    return m_weight;
}

template<typename E, typename V>
void Graph<E, V>::Edge::weight(E const& _weight)
{
    m_weight = _weight;
}

template<typename E, typename V>
bool Graph<E, V>::Edge::operator <(Edge const& _rhs) const
{
    return m_weight < _rhs.m_weight;
}

template<typename E, typename V>
bool Graph<E, V>::Edge::isInTree() const
{
    return m_isInMinTree;
}

template<typename E, typename V>
void Graph<E, V>::Edge::setInTree(bool _isInTree)
{
    m_isInMinTree = _isInTree;
}

template<typename E, typename V>
bool Graph<E, V>::CompareSecond::operator()(const MyPairType& left, const MyPairType& right) const
{
    return left.second < right.second;
}

#endif