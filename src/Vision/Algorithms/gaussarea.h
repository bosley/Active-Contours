#ifndef GAUSSAREA_H
#define GAUSSAREA_H

// https://en.wikipedia.org/wiki/Shoelace_formula

#include <list>
#include <vector>
#include <iterator>
#include <opencv2/core/core.hpp>

using namespace cv;

float GaussArea(std::vector<Point> points);

Point Centroid(std::vector<Point> points);
Point Centroid(std::list<Point> points);

#endif // GAUSSAREA_H
