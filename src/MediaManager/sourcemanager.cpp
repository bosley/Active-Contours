#include "sourcemanager.h"

SourceManager::SourceManager()
{
    cameraCount = -1;
    videoReady = false;
    camerasReady = false;
    imageReady = false;
}

bool SourceManager::isVideoReady()
{
    return videoReady;
}

bool SourceManager::isCameraReady()
{
    return camerasReady;
}

bool SourceManager::isImageReady()
{
    return imageReady;
}

int SourceManager::getSelectedCamera()
{
    return cameraSelection;
}

std::string SourceManager::getSelectedVideo()
{
    return videoFile;
}

std::string SourceManager::getSelectedImage()
{
    return imageFile;
}

void SourceManager::setSelectedVideo(std::string selection)
{
    videoFile = selection;
    videoReady = true;
}

void SourceManager::setSelectedCamera(int selection)
{
    cameraSelection = selection;
    camerasReady = true;
}

void SourceManager::setSelectedImage(std::string selection)
{
    imageFile = selection;
    imageReady = true;
}

void SourceManager::reloadCameras()
{
    cameraCount = 0;
    bool search = true;
    while (search)
    {
        cv::VideoCapture cap;
        cap.open(cameraCount++);
        if(cap.isOpened())
            cap.release();
        else
           search = false;
    }
    cameraCount--;
}

int SourceManager::getAvailableCameras()
{
    return cameraCount;
}
