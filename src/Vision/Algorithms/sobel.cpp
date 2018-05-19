#include "sobel.h"

/*
 GX             GY
    1, 0,-1,        1, 2, 1,
    2, 0,-2,        0, 0, 0,
    1, 0,-1        -1,-2,-1
*/

sobelPack FullSobel(Mat frame, int thresh, bool calcAngle, bool deadSpace)
{
    // Grayscale the image
    Mat gray;
    cvtColor(frame, gray, CV_BGR2GRAY);

    int reservedSpace = (frame.cols*frame.rows)/2;

    // Get the data to return ready
    sobelPack data;
    gray.copyTo(data.frame);
    data.contours.reserve(reservedSpace);

    if(calcAngle){
        data.angleAvailable = true;
        data.angles.reserve(reservedSpace);
    } else {
        data.angleAvailable = false;
    }

    for(int x = 1; x < gray.rows-2; x++)
    {
        for(int y = 1; y < gray.cols-2; y++)
        {
            // Bottom
            short b0 = (short)gray.at<uchar>(x-1,y-1);
            short b1 = (short)gray.at<uchar>(x,y-1);
            short b2 = (short)gray.at<uchar>(x+1,y-1);

            // Middle
            short m0 = (short)gray.at<uchar>(x-1,y);
            // Middle value (x,y) always multd by 0
            short m2 = (short)gray.at<uchar>(x+1,y);

            // Top
            short t0 = (short)gray.at<uchar>(x-1,y+1);
            short t1 = (short)gray.at<uchar>(x,y+1);
            short t2 = (short)gray.at<uchar>(x+1,y+1);

            // Reduced from matrix operations
            int px = b0 + (-b2) + (2 * m0) + (-2 * m2) + t0 + (-t2);
            int py = b0 + (2 * b1) + b2 + (-t0) + (-2 * t1) + (-t2);

            int value = static_cast<int>(std::ceil(std::sqrt((px*px) + (py*py))));
            if(value > 255)
                value = 255;


            if(value >= thresh)
            {
                data.contours.push_back(Point(x,y));
                data.frame.at<uchar>(x,y) = value;
                if(calcAngle)
                {
                    if(px != 0)
                        data.angles.push_back( std::atan(py/px) );
                    else
                        data.angles.push_back(0.0);
                }
            }
            else if (deadSpace)
            {
                // This keeps the contours the color of the original pixels
                // Because we have the points of interest, we don't need to draw
                // anything, but its usually pleasing to look at.
                // undefine SOBEL_FILL_IN_NEG_SPACE to ignore op
                data.frame.at<uchar>(x,y) = 0;
            }
        } // End Y
    }// End X
    return data;
}
