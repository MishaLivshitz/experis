#include "Scene.h"
#include "Moveable.h"

Scene::Scene(int _size)
:Group(_size)
{

}

void Scene::Move(Point const& _p)
{
    int const size = m_drawables.size();
    Moveable* item;
   
    for(int i = 0; i< size; ++i)
    {
        item = dynamic_cast<Moveable*>(m_drawables[i]);
        if(item)
        {
            item->Move(_p);
        }
    }
}