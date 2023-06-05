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
    
    MyPoint() : x(0), y(0), colorValue(0) {}
    MyPoint(int xCoord, int yCoord, int color) : x(xCoord), y(yCoord), colorValue(color) {}
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
    int set_values_color_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture&  cap);
	void color_cube_pixels(const MyPoint& start, const MyPoint& end, int pos,cv::VideoCapture& cap, cv::Mat& coloredFrame);
	int get_color_value_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture&  cap);
    // Performs calibration of the camera
    void calibrate();
    
    int detectChange();

    // Retrieves measurements points from the camera
    int** get_measurements_points();

    // Views the camera frame and displays it
    int view_frame();
    
    // Takes a picture
    int take_picture();
    
    int take_mono_picture();

private:
	int colorValues[58];
	unsigned int detectedCounter = 0;
	bool detectedRight = false, detectedMiddle = false, detectedLeft = false;

    int maxY;   // Maximum y-coordinate of the frame
    int maxX;   // Maximum x-coordinate of the frame
    int line1;  // Starting position of line 1
    int line2;  // Starting position of line 2
};

#endif // CAMERA_HPP
