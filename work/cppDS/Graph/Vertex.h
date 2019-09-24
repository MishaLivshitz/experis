#ifndef VERTEX_H
#define VERTEX_H


template<typename T>
class Vertex
{
public:
    Vertex();
    Vertex(T const&);

    bool operator< (Vertex<T> const&) const;
    bool operator== (Vertex<T> const&) const;

    T const& data() const;
    void data(T const&);

private:
    T m_data;
    bool m_isVisited;

};


template<typename T>
bool Vertex<T>::operator<(Vertex<T> const& _rhs) const
{
    return m_data < _rhs.m_data;
}

template<typename T>
bool Vertex<T>::operator== (Vertex<T> const& _rhs) const
{
    return m_data == _rhs.m_data;
}

template<typename T>
Vertex<T>::Vertex()
: m_data()
, m_isVisited(false)
{

}

template<typename T>
Vertex<T>::Vertex(T const& _data)
: m_data(_data)
, m_isVisited(false)
{
    m_data = _data;
}

template <typename T>
T const & Vertex<T>::data() const
{
    return m_data;
}

template <typename T>
void Vertex<T>::data(T const& _data)
{
    m_data = _data;
}

#endif