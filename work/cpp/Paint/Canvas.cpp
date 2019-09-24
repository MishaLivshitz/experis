#include "Canvas.h"
#include "Point.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>


Canvas::Canvas(int _height, int _width)
:m_canvasVec(_height, ColorVec(_width))
,m_height(_height)
,m_width(_width)
{
}
    
void Canvas::drawPixel(Color const& _c, Point const& _p)
{
    if(validatePoint(_p))
    {
        m_canvasVec[_p.getY()][_p.getX()] = _c;
    }
}

void Canvas::buildHeader(std::string& _str) const
{
    std::stringstream ss;
    ss << m_width <<' ' << m_height << '\n' << 255 << '\n';
    _str.append(ss.str());
}

bool Canvas::validatePoint(Point const& _p)
{
    int x = _p.getX();
    int y = _p.getY();

    return !(x > m_width-1 || x < 0 || y > m_height-1 || y < 0);
}

void Canvas::savePic(std::string const& _fileName) const
{
    std::string myFileName(_fileName);
    myFileName.append(".ppm");
    FILE* fd;
    std::string header = "P3\n";

    buildHeader(header);
    fd = fopen(myFileName.c_str(), "w");
    
    if(fd)
    {
        fprintf(fd, "%s", header.c_str());
        for(int i=0; i<m_height ; ++i)
        {
            for(int j = 0; j < m_width; ++j)
            {
                fprintf(fd,"%d %d %d ", m_canvasVec[i][j].R , m_canvasVec[i][j].G, m_canvasVec[i][j].B);
            }
            fprintf(fd, "\n");
        }

        fclose(fd);
    }
}

void Canvas::canvasSize(std::pair<int,int> & _resPair) const
{
    _resPair.first = m_canvasVec.size();    
    _resPair.second = m_canvasVec[0].size();    
}
