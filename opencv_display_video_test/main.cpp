#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    int device = 0;
    if (argc > 1)
    {
        // Use user-specified video device
        device = atoi(argv[1]);
    }
    // Open video device
    cv::VideoCapture cap;
    cap.open(device);

    if (!cap.isOpened())
    {
        std::cerr << "Could not open video source\n";
        return -1;
    }

    std::stringstream windowName;
    windowName << "/dev/video" << device;

    cv::Mat frame;
    cv::namedWindow(windowName.str(), 1);

    do
    {
        cap >> frame;

        if ( frame.empty() )
        {
            std::cerr << "cv::VideoCapture::read() returned an empty frame\n";
            continue;
        }

        cv::imshow(windowName.str(), frame);
    } while (cv::waitKey(10) < 0);

    return 0;
}
