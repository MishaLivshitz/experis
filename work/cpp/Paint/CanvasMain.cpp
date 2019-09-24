
#include "Canvas.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"
#include "RectAngle.h"
#include "Circle.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

#define RANGE_X 300
#define RANGE_Y 300
#define RANGE_COLOR 256
#define RANGE_RADIUS 100 

int main()
{
    Canvas c(1000,1000);
    unsigned char r,g,b;
    std::stringstream fileName;
    
    srand(time(0));
    for(int i = 0; i < 100; ++i)
    {
        Point p1(std::rand()%RANGE_X +150 + i*2,std::rand()% RANGE_Y +150+ i*2);
        Point p2(std::rand()%RANGE_X +150 + i*3,std::rand()% RANGE_Y +150+ i*3);
        r = std::rand()%RANGE_COLOR;
        g = std::rand()%RANGE_COLOR;
        b = std::rand()%RANGE_COLOR;

        Color col = {r,g,b};

        /* HorizontalLine hLine(col,p1,std::rand()%RANGE_X);
        VerticalLine vLine(col,p1,std::rand()%RANGE_X);*/
        RectAngle r1(col,p2,std::rand()%RANGE_X,std::rand()%RANGE_Y); 
        //Circle cir(col,p1,std::rand()%RANGE_RADIUS);
    
        r1.draw(c);
       /* vLine.draw(c);
        hLine.draw(c);  */
        //cir.draw(c);
        
        fileName << "./Frames/frame-" << i+1;
        c.savePic(fileName.str());
        fileName.str("");
    }
}