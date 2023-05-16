#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "setup.hpp"

cv::VideoCapture setup_camera();
bool check_frame();//cehcks frame if its empty
int callibrate();
int get_measurements_point(int x, int y);
int** get_measurements_points();
int view_frame();

#endif
