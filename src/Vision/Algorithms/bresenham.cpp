#include "bresenham.h"

std::vector<Point> getLow(Point lhs, Point rhs)
{
    int yi = 1;
    int y = lhs.y;
    int dx = rhs.x - lhs.x;
    int dy = rhs.y - lhs.y;

    if(dy < 0)
    {
        yi = -1;
        dy = dy - (dy*2);
    }

    int dx2 = 2*dx;
    int dy2 = 2*dy;
    int D = dy2 - dx;

    std::vector<Point> package;
    for(int x = lhs.x; x < rhs.x; x++)
    {
        package.push_back(Point(x, y));
        if(D > 0)
        {
            y = y + yi;
            D = D - dx2;
        }
        D = D + dy2;
    }
    return package;
}

std::vector<Point> getHigh(Point lhs, Point rhs)
{
    int xi = 1;
    int x = lhs.x;
    int dx = rhs.x - lhs.x;
    int dy = rhs.y - lhs.y;

    if(dx < 0)
    {
        xi = -1;
        dx = dx - (dx*2);
    }

    int dx2 = 2*dx;
    int dy2 = 2*dy;
    int D = dx2 - dy;

    std::vector<Point> package;
    for (int y = lhs.y; y < rhs.y; y++)
    {
        package.push_back(Point(x, y));
        if (D > 0)
        {
            x = x + xi;
            D = D - dy2;
        }
        D = D + dx2;
    }
    return package;
}

std::vector<Point> BresenLine(Point start, Point goal)
{
    if(std::abs(goal.y - start.y) < std::abs(goal.x - start.x))
    {
        if (start.x > goal.x)
            return getLow(goal, start);
        else
            return getLow(start, goal);
    }
    else
    {
        if(start.y > goal.y)
            return getHigh(goal, start);
        else
            return getHigh(start, goal);
    }
}
