#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <thread>
#include "setup.hpp"

struct MyPoint {
    int x;
    int y;
    int colorValue = 0;
};

class Camera {
public:
    Camera();
    ~Camera();
    cv::VideoCapture setup_camera();
    bool check_frame();
    MyPoint get_values_point(MyPoint p1);
    int get_color_value_cube(MyPoint start, MyPoint end);
    int callibrate();
    int** get_measurements_points();
    int view_frame();

private:
    int maxY;
    int maxX;
    int line1;
    int line2;
};

#endif
