#ifndef SCENE_GEN_H
#define SCENE_GEN_H

#include "Scene.h"
#include "RandomShapeFactory.h"
#include <vector>

class SceneGenerator
{

public:

    void createScene(RandomShapeFactory const& _rFact, Scene& _scene) const;
    
};


#endif