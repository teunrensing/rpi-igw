#include <iostream>
#include "camera.hpp"

void view_frame()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        return -1;
    }

    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        cv::imshow("Frame", frame);
        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }
}