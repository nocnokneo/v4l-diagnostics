#include <cv.h>
#include <highgui.h>

#include <iostream>

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
        return 1;
    }

    cv::Mat frame;

    // grab() and retrieve() a frame
    cap >> frame;

    if (!frame.empty())
    {
        cv::imwrite("frame.png", frame);
    }
    else
    {
        std::cerr << "cv::VideoCapture::read() returned an empty frame\n";
        return 1;
    }

    return 0;
}
