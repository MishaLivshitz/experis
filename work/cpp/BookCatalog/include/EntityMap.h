#ifndef Entity_MAP
#define Entity_MAP

#include <map>
#include <string>

template <typename T>
class EntityMap
{
public:
    EntityMap();
    ~EntityMap();
    //TODO: cctor and assignment Operator
    
    void add(std::string const& _name);
    T* get(std::string const& _name) const;

private:
    typedef std::map<std::string, T*> Map_t;
    Map_t m_entity;

};

template <typename T>
inline void EntityMap<T>::add(std::string const& _name)
{
    if(m_entity.find(_name) == m_entity.end())
    {
        m_entity[_name] = new T(_name);
    }
}

template <typename T>
inline T* EntityMap<T>::get(std::string const& _name) const
{
    typename Map_t::const_iterator itr = m_entity.find(_name);
    if(itr != m_entity.end())
    {
        return itr->second;
    }

    return 0;
}

template <typename T>
EntityMap<T>::EntityMap()
{
}

template <typename T>
EntityMap<T>::~EntityMap()
{
    typename Map_t::iterator itB = m_entity.begin();
    typename Map_t::iterator itE = m_entity.end();

    while(itB!=itE)
    {
        delete itB->second;
        ++itB;
    }
}

#endif