#ifndef SCENE_H
#define SCENE_H

#include "Moveable.h"
#include "Group.h"

class Scene: public Group, Moveable
{
public:
    
    Scene(int _size = 1);
    virtual void Move(Point const& _p);

};


#endif