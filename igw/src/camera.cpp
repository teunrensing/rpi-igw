#include <iostream>
#include <thread>
#include "camera.hpp"

#define maxY 360
#define maxX 640
#define line1 maxX/3
#define line2 maxX/3*2

// max x and max y from the frame. line X as starting postitions. Previous of line 1 and 2 variables until 2 positions in the past.

cv::VideoCapture setup_camera(){
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, maxX);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, maxY);
    //cap.set(cv::CAP_PROP_FPS, cap.get(cv::CAP_PROP_FPS) * 0.5);
    
    if (!cap.isOpened())
    {
        std::cout << "frame failed";
    }
    return cap;
}
bool check_frame()
{
    //Make capture of videofeed in grayscale
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
    {
        return 0;
    }
    return 1;
}
int callibrate(){
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap >> frame;

    int** result= get_measurements_points(); 
    for(int i;i<sizeof(result[0]);i++)
    {
        
    }
    for(int i;i<sizeof(result[1]);i++)
    {
        
    }
  
    // Deallocate the dynamically allocated memory
    
        for (int j = 0; j < maxY/2; j++) {
            delete[] result[j];
        }
        delete[] result;
    
    return 1;
}

int get_measurements_point(int x, int y){
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap.read(frame);
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    return grayFrame.at<uchar>(y,x);
}
int** get_measurements_points(){
    int** gray_array = new int*[2];
    for(int x=0; x<2;x++){
        gray_array[x] = new int[maxY];
    
    }
  
    int counter;
    // maybe use multithreading to make it more efficient?
    for(int y=0; y< maxY ; y++){
        gray_array[0][y] = get_measurements_point(line1, y);
        gray_array[1][y] = get_measurements_point(line2, y);
    }
  
    return gray_array;
}

int view_frame()
{
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
   // callibrate();
  
    while (true)
    {
        cap.read(frame);
        if (frame.empty())
        {
            break;
        }
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        //std::cout << "frame width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH)<< " frame height: "<< cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";
        
        // if get new frame renew parameters max width and height.
        //cv::Point pt1(cap.get(cv::CAP_PROP_FRAME_WIDTH), 200); // start point
        //cv::Point pt2(100, cap.get(cv::CAP_PROP_FRAME_HEIGHT)); // end point
        //cv::Scalar color(0, 255, 0); // green color

        //cv::line(grayFrame, pt1, pt2, color, 2);
       
        cv::imshow("GrayFrame", grayFrame);
        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
