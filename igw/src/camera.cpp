#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

Camera::Camera() : maxY(360), maxX(640), line1(210), line2(410), array_(nullptr) {
    allocate_array();
}

Camera::~Camera() {
    deallocate_array();
}

cv::VideoCapture Camera::setup_camera() {
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, maxX);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, maxY);

    if (!cap.isOpened()) {
        std::cout << "Failed to open camera.";
    }
    return cap;
}

bool Camera::check_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
        return false;
    }
    return true;
}

cv::Mat Camera::get_gray_values_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap.read(frame);
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    //p1.colorValue = grayFrame.at<uchar>(p1.y, p1.x);
    return grayFrame;
}
void Camera::set_values_cube(MyPoint start, MyPoint end, int pos) {
    // Access the array elements and perform operations
    // using the start and end points
    cv:: Mat grayFrame = get_gray_values_frame();
    MyPoint result;
    for (int i = 0; i < MYLENGTH10; i++) {
        for (int j = 0; j < MYLENGTH10; j++) {
            result.x = start.x + i;
            result.y = start.y + j;
            if(result.x != end.x -(10-i)){
                std::cout << "x values of result and end dont match"<<endl;
             break;   
            }
            if(result.y != end.y -(10-j)){
                std::cout << "y values of result and end dont match"<<endl;
             break;   
            }
            //result.colorValue = grayFrame.at<uchar>(result.y, result.x);// make a seperate loop for it so it issn't used every call.
            // Process the array
            array_[pos][i][j]= result;//Allocate the values of point;
        }
    }
}

int Camera::calibrate() {
    MyPoint lt,rt,lb,rb;
    
    //Coordinates leftside
    lt.y = maxY/2;
    lt.x = line1;
    lb.y = maxY;
    lb.x = line1;
    //Coordinates rightside
    rt.y = maxY/2;
    rt.x = line2;
    rb.y = maxY;
    rb.x = line2;
    MyPoint start,end;
    for(int i=0; i<13;i++){
        start.x =line1;
        start.y=maxY-10*i;
        end.x=line1+10;
        end.y=maxY-10*i;
        set_values_cube(start,end,i);
    }
    for(int i=13; i<34;i++){
        start.x =line1+10*i;
        start.y=maxY/2;
        end.x=line1+10+10*i;
        end.y=maxY/2;
        set_values_cube(start,end,i);
    }
    for(int i=34; i<47;i++){
        start.x =line2;
        start.y=maxY-10*i;
        end.x=line2+10;
        end.y=maxY-10*i;
        set_values_cube(start,end,i);
    }
    return 1;
}

int Camera::view_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    // calibrate();

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            break;
        }
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::imshow("GrayFrame", grayFrame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
    return 0;
}

void Camera::allocate_array() {
    array_ = new MyPoint**[MYLENGTH];
    for (int i = 0; i < MYLENGTH10; i++) {
        array_[i] = new MyPoint*[MYLENGTH10];
        for (int j = 0; j < MYLENGTH10; j++) {
            array_[i][j] = new MyPoint[MYLENGTH10];
        }
    }
}

void Camera::deallocate_array() {
    if (array_) {
        for (int i = 0; i < MYLENGTH10; i++) {
            for (int j = 0; j < MYLENGTH10; j++) {
                delete[] array_[i][j];
            }
            delete[] array_[i];
        }
        delete[] array_;
        array_ = nullptr;
    }
}
