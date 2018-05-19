#ifndef DISPWIDGET_H
#define DISPWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

#include <QDebug>

#include "videoplayer.h"
#include "Vision/tsparams.h"

class dispwidget : public QLabel
{
    Q_OBJECT
public:
    explicit dispwidget(QWidget *parent = nullptr);
    ~dispwidget();
    bool startVideo(std::string video);
    bool startCamera(int camera);
    bool startImage(std::string image);
    void stop();
    bool stopped();

    void setParams(AlgoParams *ap);

    void startAlgo();

    bool canStart();

signals:    
    void displayStopped();
    void displayStarted();
    void errorMessage(QString error);

public slots:
    void updateScreen(QImage image);
    void endOfInputFromPlayer();
    void mousePressEvent(QMouseEvent* event) override;

private:
    VideoPlayer *player;
    bool hasFirstImage;
    bool runAlgo;
    int pointsAdded;

};

#endif // DISPWIDGET_H
