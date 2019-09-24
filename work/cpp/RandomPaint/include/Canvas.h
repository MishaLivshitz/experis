#ifndef CANVAS_H
#define CANVAS_H


#include <vector>
#include <string>
#include "Color.h"
#include "Point.h"

class Canvas
{

typedef std::vector<std::vector<Color> > CanvasVec;
typedef std::vector<Color> ColorVec;
public:

    Canvas(int _height = 1, int _width = 1);
    
    void drawPixel(Color const& _c, Point const& _p);
    void savePic(std::string const&) const;

    void canvasSize(std::pair<int,int> &) const;

private:
    void buildHeader(std::string& _str) const;
    bool validatePoint(Point const& _p);

private:

  CanvasVec m_canvasVec;
  int m_height;
  int m_width;
  
};

#endif
