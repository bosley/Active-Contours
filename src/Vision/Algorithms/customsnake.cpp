#include "customsnake.h"

#ifdef CUSTOM_CONTOUR_ALG

namespace cvalg{

CustomSnake::CustomSnake()
{
    _w = 0;
    _h = 0;
    _initialDisperse = false;
}

void CustomSnake::init(int cols, int rows)
{
    _w = cols;
    _h = rows;
}
void CustomSnake::insertPoint(Point p, int pos)
{
    // Handle front and back
    if(pos == -1){
        _snake.push_back(p);
        return;
    } else if (pos == 0){
        _snake.push_front(p);
        return;
    }

    // Insert a point at the given pos
    std::list<Point>::iterator it = _snake.begin();
    std::advance(it, pos);
    _snake.insert(it, p);
}

void CustomSnake::removePoint(int pos)
{
    // Handle front and back
    if(pos == -1){
        _snake.pop_back();
        return;
    } else if (pos == 0){
        _snake.pop_front();
        return;
    }

    // Remove a point at the given pos
    std::list<Point>::iterator it = _snake.begin();
    std::advance(it, pos);
    _snake.erase(it);
}

Mat CustomSnake::drawSnake(Mat frame)
{
    std::list<Point>::iterator e = _snake.end();
    e--;
    std::list<Point>::iterator n = _snake.begin();
    n++;

    // Lines
    if(this->params->getDrawSnake())
    {
        if(static_cast<int>(_snake.size()) >= MINIMUM_POINTS)
        {
            for(std::list<Point>::iterator i = _snake.begin(); i != e; ++i)
            {
                cv::line(frame, (*i), (*n), Scalar(0,0,255),1 );
                n++;
            }
            cv::line(frame, (*e), (*_snake.begin()), Scalar(0,0,255),1 );
            // Center
            _center = Centroid(_snake);
            circle(frame, _center, 2, Scalar(0,179,255),CV_FILLED, 15,0);
        }
        // Points
        for(std::list<Point>::iterator i = _snake.begin(); i != _snake.end(); ++i)
            circle(frame, (*i), 2, Scalar(255,0,0),CV_FILLED, 50,0);
    }
    return frame;
}

Mat CustomSnake::iterate(Mat frame)
{
    frame.copyTo(_frame);

    // Calculate the gradiants in the image
    sobelPack sobelEdges = FullSobel(_frame,
                                     this->params->getSobelThreash(),
                                     this->params->getSobelAngle(),
                                     this->params->getSobelDeadSpace());
    sobelEdges.frame.copyTo(_sobelFrame);

    if(!_initialDisperse)
    {
        _initialDisperse = true;
        disperseSnakePoints();
    }

    // Ensure center is updated
    _center = Centroid(_snake);


   // qDebug() << "Start GA ";
    // Run GA cycle -  NYD
    gaCycle();

   // qDebug() << "GA Complete. New Snake size: " << _snake.size();

    /*
        Handle display options, and copy over
        data to a frame for returning to the user
    */
    Mat completedFrame;
    if(this->params->getViewSobel())
    {
        cvtColor(_sobelFrame, completedFrame, CV_GRAY2BGR);
    } else {
        _frame.copyTo(completedFrame);
    }

    // Return the frame for display
    return completedFrame;
}

void CustomSnake::gaCycle()
{
    // For init minEnergy search at end of epochs
    float worstEnergy = 0.0;
    for(int epoch = 0; epoch < this->params->getEpochPerCycle(); epoch++)
    {
        // Population
        if(_snakePool.empty())
            fillSnakePool(0);

        // For each snake, calc energy
        std::vector<float> lowEnergy;
        std::vector< std::list<Point> > topSnakes;
        for(int i = 0; i < static_cast<int>(_snakePool.size()); i++)
        {
            // Evaluation
            float energy = energyEvaluation(_snakePool[i]);
            if(energy > worstEnergy)
                worstEnergy = energy;

            // Selection
            if(static_cast<int>(topSnakes.size()) < this->params->getGenSurvive())
            {
                topSnakes.push_back(_snakePool[i]);
                lowEnergy.push_back(energy);
            }
            else
            {
                // First 'n' snakes have been filled, now a comparison must be
                // made and energy indexes updated
                bool placed = false;
                for(int j = 0;
                    j < static_cast<float>(lowEnergy.size()) && !placed; j++)
                {
                    if(energy < lowEnergy[j])
                    {
                        lowEnergy[j] = energy;
                        topSnakes[j] = _snakePool[i];
                        placed = true;
                    }
                }
            }
        } // End energy eval

        // If we are on the last epoch
        if(epoch == this->params->getEpochPerCycle()-1)
        {
            // Locate snake with lowest energy
            int lowest = 0;
            float minEnergy = worstEnergy;
            for(int j = 0; j < static_cast<float>(lowEnergy.size()); j++)
                if(lowEnergy[j] < minEnergy){
                    lowest = j;
                    minEnergy = lowEnergy[j];
                }

            // Improve the best snake just a little bit
            topSnakes[lowest] = improve(topSnakes[lowest]);
            qDebug() << "Lowest energy index: " <<  lowest;

            // Clear the snake and designate lowest energy snake as _snake
            _snake.clear();
            for(std::list<Point>::iterator si = topSnakes[lowest].begin();
                si != topSnakes[lowest].end(); si++)
                _snake.push_back((*si));

        } // End handling last epoch

        // Figure out who will mate
        std::vector< std::list<Point> > mateSnakes;
        int mates = static_cast<int>(topSnakes.size()) * this->params->getMatingRatio();
        for(int i = 0; i < mates; i++)
            mateSnakes.push_back(topSnakes[i]);

        // Kill all the bad snakes, and place only the top ones in the pool
        _snakePool.clear();



        for(int i = 0; i < static_cast<int>(topSnakes.size()); i++)
        {
            _snakePool.push_back(topSnakes[i]);
        }

        // Swap snake genes
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> xdist(0, 100);
        for(int g = 0; g < static_cast<int>(mateSnakes.size())-1; g++)
        {
            // new snake
            std::list<Point> babySnake;
            std::list<Point>::iterator ms = mateSnakes[g].begin();
            std::list<Point>::iterator me = mateSnakes[g].end();
            std::list<Point>::iterator msn = mateSnakes[g+1].begin();
            for(; ms != me; ms++)
            {
                // Swap, or not
                if(xdist(eng) < this->params->getSwapRatio())
                {
                    babySnake.push_back(Point((*msn).x, (*msn).y));
                } else {
                    babySnake.push_back(Point((*ms).x, (*ms).y));
                }
                msn++;
            }

            // Add the new snake to the pool
            _snakePool.push_back(babySnake);
        }

        // There should now be
        // GENERATION_TOP_SNAKES +
        //  (GENERATION_TOP_SNAKES*CROSSOVER_MATING_RATIO)
        // snakes in the pool
        // Now we need to fill the pool up with new snakes up-to
        // n = SNAKES_PER_GENERATION
        // SNAKES_PER_GENERATION - (surviving + mated)

        fillSnakePool(
                    this->params->getPopCount() -
                        (this->params->getGenSurvive() + mates)
                    );

    } // End EPOCH loops

}

float CustomSnake::energyEvaluation(std::list<Point> snake)
{
    // Sum the energy of all the points
    // Ignore neighborhoods tho
    std::list<Point>::iterator ss = snake.begin(); // Iterates after each pass
    std::list<Point>::iterator sb = snake.begin(); // Doesn't change
    std::list<Point>::iterator sn = snake.begin(); sn++; // Iterates each pass
    std::list<Point>::iterator se = snake.end(); se--; // Doesn't change

    float energy = 0.0;
    int pointIndex = 0;
    int endIndex = static_cast<int>(snake.size())-1;
    while(ss != se)
    {
        /*  Econt
            (δ- (x[i] - x[i-1]) + (y[i] - y[i-1]))^2
            δ = avg dist between snake points
        */
        Point prevPoint;
        if(pointIndex == 0)
        {
            prevPoint = Point(se->x, se->y);
        } else {
            ss--;
            prevPoint = Point(ss->x, ss->y);
            ss++;
        }

        // Calculate Econt
        float econt = (ss->x - prevPoint.x) + (ss->y - prevPoint.y);
        econt = std::pow(econt, 2);
        econt = averageDist(snake) - econt;

        // Multiply by alpha
        econt *= this->params->getAlpha();


        /*  Ecurv
            (x[i-1] - 2x[i] + x[i+1])^2 + (y[i-1] - 2y[i] + y[i+1])^2
        */
        Point nextPoint;
        if(pointIndex == endIndex)
            nextPoint = Point(sb->x, sb->y);
        else
            nextPoint = Point(sn->x, sn->y);

        float ecurv = std::pow( (prevPoint.x - (ss->x*2) + nextPoint.x), 2);
        ecurv += std::pow( (prevPoint.y - (ss->y*2) + nextPoint.y), 2);
        ecurv *= this->params->getBeta();

        /*  Eimage
            -||∇||

            Gradient magnitude encoded in pixel information
                - May want to change this 'feature'
        */
        float eimage = -(int)_sobelFrame.at<uchar>(ss->y,ss->x);
        eimage *= this->params->getGama();

        // Didn't normalize b/c not scanning area - might need to
        // do something else.

        energy += econt + ecurv + eimage;

        /*
                END LOOP -> Step forward
        */
        ss++; sn++;
        pointIndex++;
    }

    // Return the energy
    return energy;
}

void CustomSnake::fillSnakePool(int start)
{
  //  qDebug() << "Init snake pool ";

    // Get neighborhood size
    int block = 0;
    (this->params->getNeighborhoodBlock() % 2 == 0) ?
                block = this->params->getNeighborhoodBlock()+1 :
            block = this->params->getNeighborhoodBlock();
    block = (block-1)/2;

    // For the entire population required
    for(int i = start; i < this->params->getPopCount(); i++)
    {
        // Make a new snake
        std::list<Point> newSnake;

        // Get random numbner, and seed the gen
        std::random_device rd;
        std::mt19937 eng(rd());

        // Going through the current (seed) snake
        std::list<Point>::iterator j = _snake.begin();
        for(; j != _snake.end(); j++)
        {
            // Get x range x0 -> x1
            int x0 = (*j).x - block;
            int x1 = x0 + this->params->getNeighborhoodBlock();
            if(x0 < 0)
                x0 = 0;
            if(x1 > _w)
                x1 = _w;

            // Get y range y0 -> y1
            int y0 = (*j).y - block;
            int y1 = y0 + this->params->getNeighborhoodBlock();
            if(y0 < 0)
                y0 = 0;
            if(y1 > _h)
                y1 = _h;

            // Generate random x, y in the neighborhood
            std::uniform_int_distribution<> xdist(x0, x1);
            std::uniform_int_distribution<> ydist(y0, y1);

            int nx = xdist(eng);
            int ny = ydist(eng);

            // Add the point to the new snake
            newSnake.push_back(Point(nx,ny));
        }

        // Add the snake to the pool
        _snakePool.push_back(newSnake);
    }
}

std::list<Point> CustomSnake::improve(std::list<Point> snake)
{
    std::vector<Point> temp;
    std::vector<Point> nstarts;
    std::vector<Point> nends;

    int block = 0;
    (this->params->getNeighborhoodBlock() % 2 == 0) ?
                block = this->params->getNeighborhoodBlock()+1 :
            block = this->params->getNeighborhoodBlock();
    block = (block-1)/2;

    std::list<Point>::iterator j = snake.begin();
    for(; j != snake.end(); j++)
    {
        temp.push_back((*j));

        // Get x range x0 -> x1
        int x0 = (*j).x - block;
        int x1 = x0 + this->params->getNeighborhoodBlock();
        if(x0 < 0)
            x0 = 0;
        if(x1 > _w)
            x1 = _w;

        // Get y range y0 -> y1
        int y0 = (*j).y - block;
        int y1 = y0 + this->params->getNeighborhoodBlock();
        if(y0 < 0)
            y0 = 0;
        if(y1 > _h)
            y1 = _h;

        nstarts.push_back(Point(x0, y0));
        nends.push_back(Point(x1, y1));
    }

    std::list<Point> fin;
    for(int i = 0; i < static_cast<int>(temp.size()); i++)
    {
        fin.push_back(newPoint(i, temp, nstarts[i], nends[i]));
    }
    return fin;
}

Point CustomSnake::newPoint(int pointIndex, std::vector<Point> _points, Point start, Point end)
{
    int cols = end.x - start.x;
    int rows = end.y - start.y;

    // Location of point in center of neighborhood
    Point location = _points[pointIndex];

    bool flag = true;
    float localMin;

    int ngmax, ngmin;
    for(int y = 0; y < rows; y ++)
        for(int x = 0; x < cols; x++)
        {
            int cval = (int)_sobelFrame.at<uchar>(y + start.y,x + start.x);
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

            std::list<Point> temp;
            for(int o = 0; o < static_cast<int>(_points.size()); o++)
                temp.push_back(_points[o]);

            econt = averageDist(temp) - econt;

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
            float eimage = -(int)_sobelFrame.at<uchar>(parentY,parentX);
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


int CustomSnake::averageDist(std::list<Point> snake)
{
    std::list<Point>::iterator i = snake.begin();
    std::list<Point>::iterator n = snake.begin();
    std::list<Point>::iterator e = snake.end();
    n++; e--;
    int len = 0.0;
    len += ((*e).x - (*i).x) * ((*e).y - (*i).y);
    for(; i != e; i++)
    {
        len += ((*i).x - (*n).x) * ((*i).y - (*n).y);
        n++;
    }
    return(std::sqrt(std::abs(len))/ static_cast<int>(snake.size()));
}

void CustomSnake::disperseSnakePoints()
{
    std::vector<Point> spts;
    std::list<Point>::iterator i = _snake.begin();
    std::list<Point>::iterator n = _snake.begin();
    std::list<Point>::iterator e = _snake.end();
    n++; e--;

    // Last to first
    LineIterator is(_frame, (*e), (*i), 8);
    for(int i = 0; i < is.count; i++, ++is)
        spts.push_back(is.pos());

    // Everything else
    for(; i != e; i++)
    {
        LineIterator it(_frame, (*i), (*n), 8);
        for(int i = 0; i < it.count; i++, ++it)
            spts.push_back(it.pos());
        n++;
    }

    // Clear snake, and re-build
    _snake.clear();
    int range = static_cast<int>(spts.size()) / this->params->getDispFact();
    for(int o = range/2; o < static_cast<int>(spts.size()); o+=range)
        insertPoint(spts[o], -1);
}


} // End namespace

#endif // CUSTOM_CONTOUR_ALG
