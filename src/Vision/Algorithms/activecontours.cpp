#include "activecontours.h"

#ifdef ACTIVE_CONTOUR_ALG

namespace cvalg {

ActiveContours::ActiveContours()
{
    _w = 0; _h = 0;
    _points.clear();
    _beta = CONTOUR_BETA;
    _alpha = CONTOUR_ALPHA;
    _gamma = CONTOUR_GAMMA;
    previously_reset = false;

#ifdef USE_ANGLE_INSERTION
    _lastAngle = clock();
#endif

#ifdef USE_AVERAGE_LENGTH_BISECTION
    _lastBisect = clock();
#endif
}

void ActiveContours::init(int iw, int ih)
{
    _w = iw;
    _h = ih;
    _center = cv::Point(_w/2, _h/2);
    _points.reserve(_w*_h);
    previously_reset = false;  
}

void ActiveContours::insertPoint(Point p)
{
    if(static_cast<int>(_points.size()) >= this->params->getNumberPoints())
        return;
    std::vector<Point>::iterator it = std::find (_points.begin(), _points.end(), p);
    if(it != _points.end())
        return;
    _points.push_back(p);
}

cv::Mat cvalg::ActiveContours::iterate(cv::Mat currentFrame)
{
    Mat returnFrame;
    currentFrame.copyTo(returnFrame);

    // Take the current frame, and do sobel edge detection, threshold = 120
    // any contour with an intensity < 120 won't come back
    //  - Inside the pack is frame (Mat), contours (vector<Point>)
    //      angleAvailable (bool) to indicate if angle is calcd
    //      angles (vector<float>) giving the angles of the contours
    sobelPack sobelEdges = FullSobel(currentFrame,
                                     this->params->getSobelThreash(),
                                     this->params->getSobelAngle(),
                                     this->params->getSobelDeadSpace());

    // Check for new point insertions
    if(static_cast<int>(_points.size()) < this->params->getNumberPoints()){

#ifdef USE_ANGLE_INSERTION
        if((( clock() - _lastAngle ) / CLOCKS_PER_SEC) > ANGLE_WAIT_SEC){
            angleInsertion();
        }
#endif

#ifdef USE_AVERAGE_LENGTH_BISECTION
        // Does more harm than good

        if((( clock() - _lastBisect ) / CLOCKS_PER_SEC) > BISECT_WAIT){
            selfInsertion();
        }
#endif
    }

    // For each snake point
    for(int i = 0; i < static_cast<int>(_points.size()); i++)
    {
        // Define the neighborhood
        // Neighborhood size is 7x7 at most
        int startx, endx, starty, endy;
        (_points[i].x - 3 < 0) ? startx = 0 : startx = _points[i].x - 3;
        (_points[i].x + 4 > _w) ? endx = _w : endx = _points[i].x + 4;
        (_points[i].y - 3 < 0) ? starty = 0 : starty = _points[i].y - 3;
        (_points[i].y + 4 > _h) ? endy = _h : endy = _points[i].y +4;

        Point s(startx, starty);
        Point e(endx, endy);

        _points[i] = newPosition(
                    i, s, e, sobelEdges.frame
                    );

#ifdef DRAW_NEIGHBORS
        if(this->params->getDrawSnakePoints())
            rectangle(currentFrame, Rect(startx, starty, endx-startx, endy-starty), Scalar(0, 0, 255));
#endif
    }

    // Do any drawing that isn't really required for computation
    if(this->params->getViewSobel())
    {
        cvtColor(sobelEdges.frame, returnFrame, CV_GRAY2BGR);
    } else {
        currentFrame.copyTo(returnFrame);
    }
    return returnFrame;
}

bool ActiveContours::minimumRunReqSet()
{
    if(_points.size() >= MINIMUM_POINTS)
        return true;
    return false;
}

Mat ActiveContours::drawSnake(Mat frame)
{
    if(this->params->getDrawSnakeLines() && minimumRunReqSet())
    {
        for(unsigned long i = 0; i < _points.size()-1; i++)
            cv::line(frame, _points[i], _points[i +1], Scalar(0,255,0),1 );

        cv::line(frame, _points[0], _points[_points.size()-1], Scalar(0,255,0),1 );
    }
    if(this->params->getDrawSnakePoints() )
        for(std::vector<cv::Point>::iterator i = _points.begin(); i != _points.end(); ++i)
            circle(frame, (*i), 1, Scalar(255,0,0),CV_FILLED, 50,0);
    return frame;
}

Point ActiveContours::newPosition(int pointIndex, Point start, Point end, Mat image)
{
    int cols = end.x - start.x;
    int rows = end.y - start.y;

    // Location of point in center of neighborhood
    Point location = _points[pointIndex];

    bool flag = true;
    float localMin;

    // Update the average dist
    averagePointDistance();

    int ngmax, ngmin;
    for(int y = 0; y < rows; y ++)
        for(int x = 0; x < cols; x++)
        {
            int cval = (int)image.at<uchar>(y + start.y,x + start.x);
            if(flag){
                flag = false;
                 ngmax = cval;
                 ngmin = cval;
            } else if (cval> ngmax){
                ngmax = cval;
            } else if (cval < ngmin){
                ngmin = cval;
            }
        }

    if(ngmax == 0)
        ngmax = 1;
     if(ngmin == 0)
         ngmin = 1;

    flag = true;
    for(int y = 0; y < rows-1; y ++)
    {
        for(int x = 0; x < cols-1; x++)
        {

            /*
                E = ∫(α(s)Econt + β(s)Ecurv + γ(s)Eimage)ds
            */
            // X,Y Location in image
            int parentX = x + start.x;
            int parentY = y + start.y;

            /*  Econt
                (δ- (x[i] - x[i-1]) + (y[i] - y[i-1]))^2
                δ = avg dist between snake points
            */
            Point prevPoint;
            if(pointIndex == 0)
                prevPoint = _points[_points.size()-1];
            else
                prevPoint = _points[pointIndex-1];
            // Calculate Econt
            float econt = (parentX - prevPoint.x) + (parentY - prevPoint.y);
            econt = std::pow(econt, 2);

            econt = _avgDist - econt;

            // Multiply by alpha
            econt *= this->params->getAlpha();

            /*  Ecurv
                (x[i-1] - 2x[i] + x[i+1])^2 + (y[i-1] - 2y[i] + y[i+1])^2
            */
            Point nextPoint;
            if(pointIndex == static_cast<int>(_points.size()-1))
                nextPoint = _points[0];
            else
                nextPoint = _points[pointIndex+1];

            float ecurv = std::pow( (prevPoint.x - (parentX*2) + nextPoint.x), 2);
            ecurv += std::pow( (prevPoint.y - (parentY*2) + nextPoint.y), 2);
            ecurv *= this->params->getBeta();

            /*  Eimage
                -||∇||

                Gradient magnitude encoded in pixel information
                    - May want to change this 'feature'
            */
            float eimage = -(int)image.at<uchar>(parentY,parentX);
            eimage *= this->params->getGama();


            // Normalize
            econt /= ngmax;
            ecurv /= ngmax;

            int divisor = ngmax-ngmin;
            if (divisor <= 0)
                divisor = 1;
            eimage = (eimage-ngmin) / divisor;

            float energy = econt + ecurv + eimage;

            if(flag){
                flag = false;
                localMin = energy;
                location = Point(parentX, parentY);
            } else if (energy < localMin){
                localMin = energy;
                location = Point(parentX, parentY);
            }
        }
    }

    // Return The (new) location
    return location;
}

void ActiveContours::averagePointDistance()
{
    float sum = 0.0;
    for(int i = 0; i < static_cast<int>(_points.size()-1); i++)
    {
        sum += std::sqrt(
        ((_points[i].x - _points[i+1].x)*(_points[i].x - _points[i+1].x))+
        ((_points[i].y - _points[i+1].y)*(_points[i].y - _points[i+1].y)));
    }
    sum += std::sqrt(
    ((_points[_points.size()-1].x - _points[0].x)*
            (_points[_points.size()-1].x - _points[0].x))+
    ((_points[_points.size()-1].y - _points[0].y)*
            (_points[_points.size()-1].y - _points[0].y)));
    _avgDist = sum / _points.size();
}

#ifdef USE_ANGLE_INSERTION
void ActiveContours::angleInsertion()
{
    Point newPoint;
    int location = -1;

    for(int i = 1; i < static_cast<int>(_points.size()-1); i++)
    {
        Point prev = _points[i-1];
        Point next = _points[i+1];
        float a2 = (
                    (next.x - prev.x)*(next.x - prev.x) +
                    (next.y - prev.y)*(next.y - prev.y)
                    );
        float b2 = (
                    (_points[i].x - next.x)*(_points[i].x - next.x) +
                    (_points[i].y - next.y)*(_points[i].y - next.y)
                    );
        float c2 = (
                    (_points[i].x - prev.x)*(_points[i].x - prev.x) +
                    (_points[i].y - prev.y)*(_points[i].y - prev.y)
                    );
        float a = std::sqrt(a2);
        float c = std::sqrt(c2);
        float angle = std::acos((b2 + c2 - a2)/(2*c*a));

        if(std::isnan(angle))
            return;

        if(angle > ANGLE_LOWER_BOUND && angle < ANGLE_UPPER_BOUND)
        {
            std::vector<Point> between = BresenLine(_points[i], _points[i+1]);
            newPoint = between[(between.size()-1)/2];
            location = i;
            break;
        }
    }

    _lastAngle = clock();
    if(location == -1)
        return;

    // Insert a new point
    std::vector<Point>::iterator it = _points.begin();
    _points.insert(it+location, newPoint);
}
#endif

#ifdef USE_AVERAGE_LENGTH_BISECTION
// Not used - Needs to have variance check or something -
//  does more bad than good
void ActiveContours::selfInsertion()
{
    std::vector<int> locations;
    std::vector<Point> newPoints;
    float av2 = _avgDist*_avgDist;
    for(int i = 0; i < static_cast<int>(_points.size()-1); i++)
    {
        float dist = (_points[i].x - _points[i+1].x)*(_points[i].x - _points[i+1].x) +
                        (_points[i].y - _points[i+1].y)*(_points[i].y - _points[i+1].y);
        if(dist > av2)
        {
            locations.push_back(i);
            std::vector<Point> points = BresenLine(_points[i],_points[i+1]);
            newPoints.push_back(
                        points[points.size()/2]
                        );
        }
    }

    _lastBisect = clock();
    if(locations.size() == 0)
        return;
    std::vector<Point>::iterator it = _points.begin();
    for(int i = 0; i < static_cast<int>(locations.size()); i++)
    {
        _points.insert(it+locations[i]+i, newPoints[i]);
    }
}
#endif

}
#endif // ACTIVE_CONTOUR_ALG

