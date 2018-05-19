#include "gaussarea.h"

// Gauss Area
float GaussArea(std::vector<Point> points)
{
    float sum = 0;
    for(int i = 0; i < static_cast<int>(points.size())-1; i++)
    {
        sum += (points[i].x * points[i+1].y) - (points[i].y * points[i+1].x);
    }
    return std::abs(sum*0.5);
}

Point Centroid(std::vector<Point> points)
{
    int x = 0; int y = 0;
    for(int i = 0; i < static_cast<int>(points.size()); i++)
    {
        x += points[i].x;
        y += points[i].y;
    }
    y /= static_cast<int>(points.size());
    x /= static_cast<int>(points.size());
    return Point(x , y );
}

Point Centroid(std::list<Point> points)
{
    std::list<Point>::iterator it = points.begin();
    int x = 0; int y = 0;
    for(; it != points.end(); it++)
    {
        x += (*it).x;
        y += (*it).y;
    }
    int size = static_cast<int>(points.size());
    if(y == 0)
        y = 1;
    if(x == 0)
        x = 1;
    if(size == 0)
       size = 1;
    return Point(x / size , y / size );
}
