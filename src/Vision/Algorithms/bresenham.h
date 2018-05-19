#ifndef BRESENHAM_H
#define BRESENHAM_H

// Derived from wikipedia
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm


// cv::Point used to ensure type-conversion not required
// when working in OpenCV algorithm
#include <vector>
#include <opencv2/core/core.hpp>

using namespace cv;

// Returns all points on the line between two points
std::vector<Point> BresenLine(Point start, Point goal);

#endif // BRESENHAM_H
