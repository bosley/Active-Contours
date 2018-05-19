#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

// Class derived from online tutorial
// http://codingexodus.blogspot.com/2012/12/working-with-video-using-opencv-and-qt.html

#include <queue>
#include <string>
#include <QMutex>
#include <QImage>
#include <QThread>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Vision/tsparams.h"

#include <QDebug>

// Algorithms

#ifdef ACTIVE_CONTOUR_ALG
#include "Vision/Algorithms/activecontours.h"
#endif

#ifdef CUSTOM_CONTOUR_ALG
#include "Vision/Algorithms/customsnake.h"
#endif

using namespace cv;

class VideoPlayer : public QThread
{
    Q_OBJECT
public:
    VideoPlayer(QObject *parent = 0);
    ~VideoPlayer();
    bool loadFile(std::string file);
    bool loadCamera(int camera);
    bool loadImage(std::string image);
    void Play();
    void Stop();
    bool isStopped() const;

    void setAlgoParams(AlgoParams *ap);

    void insertClick(int x, int y);

    void startAlgo();

signals:
      void processedImage(const QImage &image);
      void endOfInput();

protected:
     void run();
     void msleep(int ms);

private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;

    bool isStatic;
    bool externalAlgoFlag;

    // Algorithm pass through - so we don't have to edit
    // anything in the video player when we change algos
    bool initialized;
    void initAlgo();
    void runAlgo();

    std::queue<Point> poi;

#ifdef ACTIVE_CONTOUR_ALG
    cvalg::ActiveContours activeContourAlg;
#endif

#ifdef CUSTOM_CONTOUR_ALG
    cvalg::CustomSnake customContourAlg;
#endif
};

#endif // VIDEOPLAYER_H
