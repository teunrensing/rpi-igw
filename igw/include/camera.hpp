#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <thread>
#include "setup.hpp"

#define MYLENGTH10 10
#define MYLENGTH20 20
#define MYLENGTH 92

// Structure to represent a point with x, y coordinates and a color value
struct MyPoint {
    int x;
    int y;
    int colorValue = 0;
};

// Class representing a camera
class Camera {
public:
    // Constructor
    Camera();

    // Destructor
    ~Camera();

    // Sets up the camera by configuring frame width, frame height, etc.
    cv::VideoCapture setup_camera();

    // Gets the color value of a specific point in the frame
    cv::Mat get_gray_values_frame();

    // Gets the color value of a cube defined by a start and end point
   int set_values_cube(MyPoint start, MyPoint end, int pos);

    // Performs calibration of the camera
    int calibrate();

    // Retrieves measurements points from the camera
    int** get_measurements_points();

    // Views the camera frame and displays it
    int view_frame();
    
    // Takes a picture
    int take_picture();
    
    int take_mono_picture();

    // Allocates memory for the 2D array
    void allocate_array();

    // Deallocates memory for the 2D array
    void deallocate_array();

private:
    int maxY;   // Maximum y-coordinate of the frame
    int maxX;   // Maximum x-coordinate of the frame
    int line1;  // Starting position of line 1
    int line2;  // Starting position of line 2
    MyPoint*** array_;  // 2D array of MyPoints
};

#endif // CAMERA_HPP
