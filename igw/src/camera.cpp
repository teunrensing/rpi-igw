#include <iostream>
#include "camera.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

int view_frame()
{
    cv::VideoCapture cap(0);
    //cap.set(cv::CAP_PROP_CONVERT_RGB, true);
    
    if (!cap.isOpened())
    {
        return -1;
    }
    cv::Mat frame;
 

 
    // get the pixel value at (x, y)
    //cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
   
 
    while (true)
    {
        
        cap >> frame;
        if (frame.empty())
        {
            break;
        }
        int maxY = frame.rows;
        int maxX = frame.cols;
        int line1 = maxX/3;
        int line2 = maxX/3*2;

        cv::Point pt1(line1, maxY/2); // start point
        cv::Point pt2(line1, maxY); // end point
        cv::Scalar color(0, 255, 0); // green color

        cv::line(frame, pt1, pt2, color, 2);
        cv::imshow("Frame", frame);
        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }
}
