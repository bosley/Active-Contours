#ifndef CUSTOMSNAKE_H
#define CUSTOMSNAKE_H

#include "Vision/tsparams.h"

#ifdef CUSTOM_CONTOUR_ALG

#include <list>
#include <vector>
#include <random>
#include <queue>
#include <iterator>
#include "Vision/Algorithms/gaussarea.h"
#include "Vision/Algorithms/bresenham.h"

#include <QDebug>

namespace cvalg{

using namespace cv;

// Custom snake algorithm
class CustomSnake
{
public:
    CustomSnake();

    // Initialize with startup information
    void init(int cols, int rows);

    // Inserts a point into list (-1 = last)
    void insertPoint(Point p, int pos);

    // Removes a point in list
    void removePoint(int pos);

    // Draws the features
    Mat drawSnake(Mat frame);

    // Steps the algorithm
    Mat iterate(Mat frame);

    // Params set by user (stay public)
    AlgoParams *params;

private:
    // Image info
    int _w;
    int _h;
    bool _initialDisperse;

    // Snake info - List for performance over vectors
    // with potential adding and removing random elements
    std::list<Point> _snake;

    //std::queue<Point> _topSnakes;
    std::vector< std::list<Point> > _snakePool;

    Mat _frame;
    Mat _sobelFrame;
    Point _center;

    // Genetic Alg Cycle
    void gaCycle();

    // Calculate energy of a snake
    float energyEvaluation(std::list<Point> snake);

    // Using initial snake (user-defined) generate
    // the first pool of snakes
    void fillSnakePool(int start);

    std::list<Point> improve (std::list<Point> snake);
    Point newPoint(int pointIndex, std::vector<Point> snake, Point start, Point end);

    // Calculate snake av point dist
    int averageDist(std::list<Point> snake);

    // Disperse snake points evenly
    void disperseSnakePoints();
};

}
#endif //CUSTOM_CONTOUR_ALG
#endif // CUSTOMSNAKE_H
