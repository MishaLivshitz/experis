#include "SceneGenerator.h"

void SceneGenerator::createScene(RandomShapeFactory const& _rFact, Scene& _scene) const
{
    size_t const capacity = _scene.capacity();
    for(size_t i = 0 ;i< capacity; ++i)
    {
        _scene.add(_rFact.createShape());
    }
}