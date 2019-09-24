#ifndef GROUP_H
#define GROUP_H

#include "Drawable.h"
#include <vector>


class Group: public Drawable
{

public:
    Group(int _size = 1);
    ~Group();
    virtual void draw(Canvas& _c) const;
    void add(Drawable const* _drawable);
    size_t capacity() const;
    void capacity(size_t _capacity);

protected:
    std::vector<Drawable*> m_drawables;

};

#endif