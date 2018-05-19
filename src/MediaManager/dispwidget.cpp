#include "dispwidget.h"

dispwidget::dispwidget(QWidget *parent) : QLabel(parent)
{
    runAlgo = false;
    hasFirstImage = false;
    pointsAdded = 0;
    player = new VideoPlayer();
    QObject::connect(player, SIGNAL(processedImage(QImage)),
                     this, SLOT(updateScreen(QImage)));
    QObject::connect(player, SIGNAL(endOfInput()),
                     this, SLOT(endOfInputFromPlayer()));
}

dispwidget::~dispwidget()
{
    delete player;
}

void dispwidget::updateScreen(QImage img)
{
    if (!img.isNull())
    {
        if(!hasFirstImage)
            hasFirstImage = true;

        this->setAlignment(Qt::AlignCenter);
        this->setPixmap(QPixmap::fromImage(img));

        /*

        // Re-scaling the image will cause coordinate mis-alignment with user-clicks when
        // drawing them on the image

        this->setPixmap(QPixmap::fromImage(img).scaled(this->size(),
                                                       Qt::KeepAspectRatio, Qt::FastTransformation));

        */
    }
}

void dispwidget::endOfInputFromPlayer()
{
    emit displayStopped();
    emit errorMessage("End of media input");
}

void dispwidget::mousePressEvent(QMouseEvent *event)
{
    if(!hasFirstImage || runAlgo)
        return;

    // Offset the click to ensure we map to the image correctly
    int xo = 0;
    int yo = 0;
    if ((this->width() != this->pixmap()->width()) && (this->pixmap()->width() > 0))
        xo = (this->width() - this->pixmap()->width()) /2;
    if ((this->height() != this->pixmap()->height()) && (this->pixmap()->height() > 0))
        yo = (this->height() - this->pixmap()->height()) /2;

    xo = event->x()-xo;
    yo = event->y()-yo;

    // Ensure that the offset clicks reside within the image
    if((xo > this->pixmap()->width()) || (xo < 0))
        return;
    if((yo > this->pixmap()->height()) || (yo < 0))
        return;

    // Send the click to the player
    player->insertClick(xo, yo);
    pointsAdded++;
    event->accept();
}

bool dispwidget::startVideo(std::string video)
{
    if (!player->loadFile(video))
    {
        emit errorMessage("Unable to load video.");
        emit displayStopped();
        return false;
    }
    else
    {
        player->Play();
        emit displayStarted();
    }
    return true;
}

bool dispwidget::startCamera(int camera)
{
    if (!player->loadCamera(camera))
    {
        emit errorMessage("Unable to load camera.");
        emit displayStopped();
        return false;
    }
    else
    {
        player->Play();
        emit displayStarted();
    }
    return true;
}
bool dispwidget::startImage(std::string image)
{
    if (!player->loadImage(image))
    {
        emit errorMessage("Unable to load image.");
        emit displayStopped();
        return false;
    }
    else
    {
        player->Play();
        emit displayStarted();
    }
    return true;
}

void dispwidget::stop()
{
    if(!player->isStopped())
    {
        player->Stop();
    }
    emit displayStopped();
}

bool dispwidget::stopped()
{
    return player->isStopped();
}

void dispwidget::setParams(AlgoParams *ap)
{
    player->setAlgoParams(ap);
}

void dispwidget::startAlgo()
{
    runAlgo = true;
    player->startAlgo();
}

bool dispwidget::canStart()
{
    return(pointsAdded >= MINIMUM_POINTS);
}

