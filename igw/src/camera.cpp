#include <iostream>
#include <thread>
#include "camera.hpp"

int maxY,maxX,line1,line2, prev1_rl1=0, prev1_rl2=0, prev2_rl1=0, prev2_rl2=0;
// max x and max y from the frame. line X as starting postitions. Previous of line 1 and 2 variables until 2 positions in the past.

bool setup_camera(){
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_CONVERT_RGB, true);
    
    if (!cap.isOpened())
    {
        return 0;
    }else{
        return 1;   
    }
    
 
}
int callibrate(int *mX, int *mY, int *l1, int *l2, int *p1rl1, int*p1rl2, int *p2rl1, int *p2rl2){
    cv::VideoCapture cap(0);
    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
    {
        return 0;
    }
    *mX = frame.rows;
    *mY = frame.cols;
    *l1 = maxX/3;
    *l2 = maxX/3*2;

    int result[]= get_measurements_points(); 
    // try with pointers to safe results from the funtion above
    *p2rl1 =*p1rl1; 
    *p2rl2 =*p1rl2;
    *p1rl1 = result[0];
    *p1rl2 = result[1];
    return 1;
}
int get_measurements_point(int x, int y){
    int result;
    cv::VideoCapture cap(0);
    cv::Mat frame;
    cap >> frame;
    cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
    result = (pixel[0] + pixel[1] + pixel[2])/3;
    return result;
}
int get_measurements_points(){
    int result[2];
    int result_line1, result_line2, counter;
    for(int i=maxY/2; i< maxY ; i+10){
        result_line1 += get_measurements_point(line1, i);
        result_line2 += get_measurements_point(line2, i);
        counter= i;
    }
    result[0]=result_line1/counter;
    result[1]=result_line2/counter;
    return result;
}

int view_frame(bool x)
{
    if(!x){
       return -1;
    }
    callibrate(&maxX,&maxY,&line1,&line2,&prev1_rl1, &prev1_rl2, &prev2_rl1, &prev2_rl2);
    cv::VideoCapture cap(0);
    cv::Mat frame;
 
    // get the pixel value at (x, y)
    //cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
 
    while (x)
    {
        
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

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
