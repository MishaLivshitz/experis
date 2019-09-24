#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Canvas.h"

class Drawable
{
public:
    virtual void draw(Canvas& _canvas) const = 0;
    virtual ~Drawable(){};
};

#endif