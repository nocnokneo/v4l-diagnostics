#include <cv.h>
#include <highgui.h>

#include <sys/time.h>
#include <signal.h>

#include <sstream>

bool terminate_requested = false;

// Elapsed time from t0 to t1 as a floating point number in ms
inline double difftime(const timeval &t1, const timeval &t0)
{
    return (t1.tv_sec  - t0.tv_sec)  * 1000.0 +
           (t1.tv_usec - t0.tv_usec) / 1000.0;
}

void termination_handler(int signum)
{
    printf("\nQuitting...\n");
    terminate_requested = true;
}

void install_termination_handler()
{
    struct sigaction new_action, old_action;

    /* Set up the structure to specify the new action. */
    new_action.sa_handler = termination_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction (SIGINT, &new_action, NULL);
    }
}

int main(int argc, char* argv[])
{
    bool display_video = false;
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
        fprintf(stderr, "Could not open video source\n");
        return -1;
    }

    cv::Mat frame;
    std::stringstream windowName;

    if (display_video)
    {
        windowName << "/dev/video" << device;
        cv::namedWindow(windowName.str(), 1);
    }

    int received_frames = 0;
    timeval previous_timestamp;

    // Start by assuming the FPS property is supported by the current V4L
    // driver implementation
    bool prop_fps_is_supported = true;
    install_termination_handler();
    while (cap.grab() && !terminate_requested)
    {
        if ( ! cap.retrieve(frame) )
        {
            fprintf(stderr, "cv::VideoCapture::retrieve() failed\n");
            return -1;
        }

        if ( frame.empty() )
        {
            fprintf(stderr, "cv::VideoCapture::retrieve() returned an empty frame\n");
            //continue;
            return -1;
        }

        ++received_frames;
        timeval current_timestamp;
        gettimeofday(&current_timestamp, NULL);
        if (received_frames > 1)
        {
            // calculate current FPS
            double fps = 1000.0 / difftime (current_timestamp,
                                            previous_timestamp);
            printf("FPS = %02.3f", fps);
        }
        memcpy(&previous_timestamp, &current_timestamp, sizeof(timeval));

        if (prop_fps_is_supported)
        {
            double prop_fps = cap.get(CV_CAP_PROP_FPS);
            if (prop_fps > 0.0)
            {
                printf(" CV_CAP_PROP_FPS = %02.3f", prop_fps);
            }
            else
            {
                prop_fps_is_supported = false;
            }
        }
        printf("\n");

        if (display_video)
        {
            cv::imshow(windowName.str(), frame);
            if(cv::waitKey(10) >= 0) break;
        }
    }

    return 0;
}
