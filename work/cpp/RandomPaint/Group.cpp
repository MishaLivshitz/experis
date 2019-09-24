#include "Group.h"


Group::Group(int _capacity)
: m_drawables()
{
    m_drawables.reserve(_capacity);
}

Group::~Group()
{
    size_t const size =  m_drawables.size();
    for(size_t i=0; i< size ;++i)
    {
        delete m_drawables[i];
    }
}

size_t Group::capacity() const
{
    return m_drawables.capacity();
}

void Group::capacity(size_t _capacity)
{
    if(m_drawables.capacity()<_capacity)
    {
        m_drawables.reserve(_capacity);
    }
}

void Group::add(Drawable const* _drawable)
{
    m_drawables.push_back((Drawable*)_drawable);
}

void Group::draw(Canvas& _c) const
{
    const int size = m_drawables.size();
    for(int i=0 ; i < size ; ++i)
    {
        m_drawables[i]->draw(_c);
    }
}