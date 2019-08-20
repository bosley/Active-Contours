#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent)
    : QThread(parent)
{
    stop = true;
    isStatic = false;
    externalAlgoFlag = false;
}

VideoPlayer::~VideoPlayer()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool VideoPlayer::loadCamera(int camera)
{
    capture.open(camera);

    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
    {
        return false;
    }
}

bool VideoPlayer::loadImage(std::string image)
{
    capture.open(image);
    if (capture.isOpened())
    {
        isStatic = true;
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
    {
        return false;
    }
}

bool VideoPlayer::loadFile(std::string file)
{
    capture.open(file);
    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
    {
        return false;
    }
}

void VideoPlayer::Play()
{
    if (!isRunning())
    {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void VideoPlayer::Stop()
{
    mutex.lock();
    stop = true;
    condition.wakeOne();
    mutex.unlock();
}

bool VideoPlayer::isStopped() const
{
    return stop;
}

void VideoPlayer::setAlgoParams(AlgoParams *ap)
{
#ifdef ACTIVE_CONTOUR_ALG
    activeContourAlg.params = ap;
#endif

#ifdef CUSTOM_CONTOUR_ALG
    customContourAlg.params = ap;
#endif
}

void VideoPlayer::insertClick(int x, int y)
{
    mutex.lock();
    poi.push(Point(x,y));
    condition.wakeOne();
    mutex.unlock();
}

void VideoPlayer::startAlgo()
{
    mutex.lock();
    externalAlgoFlag = true;
    condition.wakeOne();
    mutex.unlock();
}

void VideoPlayer::run()
{
    initialized = false;
    int delay = (1000/frameRate);

    // For single image processing
    if(isStatic)
    {
        Mat original;

        if (!capture.read(frame))
        {
            stop = true;
        }

        frame.copyTo(original);

        while(!stop)
        {
            if(!initialized)
            {
                // Initialize the algo - after first frame capd
                initAlgo();
            }

            // Will run the currently active algo, and
            // update the frame matrixx
            runAlgo();

            if (frame.channels()== 3){
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                                  RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(frame.data),
                                     frame.cols,frame.rows,QImage::Format_Indexed8);
            }

            emit processedImage(img);
            original.copyTo(frame);
            this->msleep(delay);
        }
        return;
    }

    while(!stop)
    {

        if(!capture.read(frame) || frame.empty())
        {
            stop = true;
            emit endOfInput();
        }

        if(!initialized)
        {
            // Initialize the algo - after first frame capd
            initAlgo();
        }

        // Will run the currently active algo, and
        // update the frame matrix
        runAlgo();

        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        emit processedImage(img);
        this->msleep(delay);
    }
}

void VideoPlayer::msleep(int ms)
{
 //   struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
 //   nanosleep(&ts, NULL);
}

/*
    Algorithm Functions
*/

void VideoPlayer::initAlgo()
{
#ifdef ACTIVE_CONTOUR_ALG
    activeContourAlg.init(frame.cols, frame.rows);
#endif

#ifdef CUSTOM_CONTOUR_ALG
    customContourAlg.init(frame.cols, frame.rows);
#endif

    // Ensure that init only happens once
    initialized = true;
}

void VideoPlayer::runAlgo()
{
#ifdef ACTIVE_CONTOUR_ALG

    // Insert Points despite alg running
    if(poi.size() > 0)
    {
        mutex.lock();
        while(poi.size() != 0)
        {
            activeContourAlg.insertPoint(poi.front());
            poi.pop();
        }
        condition.wakeOne();
        mutex.unlock();
    }

    // If alg is set to run - run it
    if(externalAlgoFlag)
    {
        if(activeContourAlg.previously_reset)
        {
            initAlgo();
        }

        Mat newFrame = activeContourAlg.iterate(frame);
        newFrame.copyTo(frame);
    }


    // Draw the snake if the settings on despite if we are running the algo
    // so the user can see where they are clicking
    Mat nf = activeContourAlg.drawSnake(frame);
    nf.copyTo(frame);
#endif

#ifdef CUSTOM_CONTOUR_ALG

    if(poi.size() > 0)
    {
        mutex.lock();
        while(poi.size() != 0)
        {
            customContourAlg.insertPoint(poi.front(), -1);
            poi.pop();
        }
        condition.wakeOne();
        mutex.unlock();
    }

    if(externalAlgoFlag)
    {
        Mat newFrame = customContourAlg.iterate(frame);
        newFrame.copyTo(frame);
    }
    Mat nf = customContourAlg.drawSnake(frame);
    nf.copyTo(frame);
#endif

}
