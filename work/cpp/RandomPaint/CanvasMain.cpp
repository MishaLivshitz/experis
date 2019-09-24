
#include "RandomShapeFactory.h"
#include "SceneGenerator.h"
#include "Scene.h"
#include <string>
#include <sstream>
#include "PowerCurve.h"

int main(int argc, char* argv[])
{

   int sceneCapacity = 30;
   int groupCapacity = 5;

   if(argc == 3)
   {
      sceneCapacity = atoi(argv[1]);
      groupCapacity = atoi(argv[2]);
      
   }

   RandomShapeFactory rFact(650);
   SceneGenerator sGen;
   Scene scene(sceneCapacity);
   Canvas c(1080,1920);
   std::stringstream name;

   scene.add(rFact.createGroup(groupCapacity));
   sGen.createScene(rFact,scene);
   for(int i = 0 ;i<100; ++i)
   {
      name<< "./Frame/scene"<< i + 1;
      scene.draw(c);
      c.savePic(name.str());
      scene.Move(Point(i/2,i/4));
      name.str("");
   }
}