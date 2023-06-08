#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

const int startPosX[]={210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410};
const int startPosY[]={130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350};

Camera::Camera() : maxY(360), maxX(640), line1(210), line2(410) {
    
}

Camera::~Camera() {
}

cv::VideoCapture Camera::setup_camera() {
    // Create a VideoCapture object for accessing the camera
    cv::VideoCapture cap(0);
    
    // Set the frame width and height properties of the VideoCapture object
    cap.set(cv::CAP_PROP_FRAME_WIDTH, maxX);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, maxY);

    // Check if the camera is successfully opened
    if (!cap.isOpened()) {
        std::cout << "Failed to open camera.";
    }
    
    // Return the VideoCapture object
    return cap;
}

void Camera::calibrate() {
    // std::cout << "start calibrate" << std::endl;
    
    // Set up the camera and obtain a VideoCapture object
    cv::VideoCapture cap = setup_camera();
    
    // Declare variables for storing frame and start/end points
    cv::Mat frame;
    MyPoint start, end;
    
    // Check if the frame is empty
    if (frame.empty()) {
        std::cout << "empty frame" << std::endl;
    }
    
    // Calibrate color values for the first set of cubes
    for (int i = 0; i < (sizeof(startPosY) / sizeof(startPosY[0])); i++) {
        start.x = line1;
        start.y = startPosY[i];
        end.x = start.x + 9;
        end.y = start.y + 9;
        
        // Call set_values_color_cube to set the color values for the cube
        set_values_color_cube(start, end, i, cap);
    }
    
    // Calibrate color values for the second set of cubes
    for (int i = 0; i < (sizeof(startPosY) / sizeof(startPosY[0])); i++) {
        start.x = line2;
        start.y = startPosY[i];
        end.x = start.x + 9;
        end.y = start.y + 9;
        
        // Call set_values_color_cube to set the color values for the cube
        set_values_color_cube(start, end, i + 23, cap);
    }
    
    // Calibrate color values for the third set of cubes
    for (int i = 0; i < (sizeof(startPosX) / sizeof(startPosX[0])); i++) {
        start.x = startPosX[i];
        start.y = 130;
        end.x = line2 - 1;
        end.y = start.y + 9;
        
        // Call set_values_color_cube to set the color values for the cube
        set_values_color_cube(start, end, i + 46, cap);
    }
    
    // Release the VideoCapture object
    cap.release();
    
    // std::cout << "end calibrate" << std::endl;
}

int Camera::detectChange() {
    // Set up the camera and obtain a VideoCapture object
    cv::VideoCapture cap = setup_camera();
    
    // Declare variables for storing frame, sensitivity, range, and start/end points
    cv::Mat frame;
    int sens = 20;
    const int range = 23; //(sizeof(startPosY) / sizeof(startPosY[0]));
    MyPoint start, end;
    
    // Check if the frame is empty
    if (frame.empty()) {
        std::cout << "empty frame" << std::endl;
    }
    
    // Detect changes in the left set of cubes
    for (int i = 0; i < range; i++) {
        start.x = line1;
        start.y = startPosY[i];
        end.x = start.x + 9;
        end.y = start.y + 9;
        
        // Get the current color value for the cube
        int currentValue = get_color_value_cube(start, end, i, cap);
        
        // Compare the current value with the default value and check if it exceeds the sensitivity threshold
        if ((currentValue - colorValues[i]) < -sens || (currentValue - colorValues[i]) > sens) {
            detectedCounter++;
            detectedLeft = true;
            std::cout << "Current value: " << currentValue << " Default value: " << colorValues[i] << " Print i: " << i << std::endl;
            std::cout << "Detected a change at the left, the total changes detected are: " << detectedCounter << std::endl;
            break;
        } else {
            // Handle case when no change is detected
        }
    }
    
    // Detect changes in the right set of cubes
    for (int i = 0; i < range; i++) {
        start.x = line2;
        start.y = startPosY[i];
        end.x = start.x + 9;
        end.y = start.y + 9;
        
        // Get the current color value for the cube
        int currentValue = get_color_value_cube(start, end, i + range, cap);
        
        // Compare the current value with the default value and check if it exceeds the sensitivity threshold
        if ((currentValue - colorValues[i + range]) < -sens || (currentValue - colorValues[i + range]) > sens) {
            detectedCounter++;
            detectedRight = true;
            std::cout << "Current value: " << currentValue << " Default value: " << colorValues[i + range] << " Print i: " << i + range << std::endl;
            std::cout << "Detected a change at the right, the total changes detected are: " << detectedCounter << std::endl;
            break;
        } else {
            // Handle case when no change is detected
        }
    }

    // Detect changes in the middle set of cubes
    for (int i = 0; i < (sizeof(startPosX) / sizeof(startPosX[0])); i++) {
        start.x = startPosX[i];
        start.y = 130;
        end.x = line2 - 1;
        end.y = start.y + 9;
        
        // Get the current color value for the cube
        int currentValue = get_color_value_cube(start, end, i + range * 2, cap);
        
        // Compare the current value with the default value and check if it exceeds the sensitivity threshold
        if ((currentValue - colorValues[i + range * 2]) < -sens || (currentValue - colorValues[i + range * 2]) > sens) {
            detectedCounter++;
            detectedMiddle = true;
            std::cout << "Current value: " << currentValue << " Default value: " << colorValues[i + range * 2] << " Print i: " << i + range * 2 << std::endl;
            std::cout << "Detected a change at the middle, the total changes detected are: " << detectedCounter << std::endl;
            break;
        } else {
            // Handle case when no change is detected
        }
    }
    
    // Release the VideoCapture object
    cap.release();
    
    return 0;
}

int Camera::set_values_color_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture& cap) {
    // Capture a frame from the video using the video capture 'cap'
    cv::Mat frame;
    cap.read(frame);

    // Convert the captured frame to grayscale
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    int colorValue = 0;
    int totalColorValue = 0;
    
    // Iterate over the cube's region of interest
    for (int i = 0; i < MYLENGTH10; i++) {
        MyPoint result;
        result.y = start.y + i;

        /*
        // Check if the y-values of 'result' and 'end' match
        if (result.y != end.y - (MYLENGTH10 - i)) {
            std::cout << "y values of result and end don't match" << std::endl;
            std::cout << "result.y: " << result.y << ", expected: " << end.y + (MYLENGTH10 - i) << std::endl;
            return -1;
        }
        */

        for (int j = 0; j < MYLENGTH10; j++) {
            result.x = start.x + j;

            /*
            // Check if the x-values of 'result' and 'end' match
            if (result.x != end.x - (MYLENGTH10 - j)) {
                std::cout << "x values of result and end don't match" << std::endl;
                std::cout << "result.x: " << result.x << ", expected: " << end.x - (MYLENGTH10 - j) << std::endl;
                return -1;
            }
            */

            // Accumulate the color value at the current pixel location
            colorValue += grayFrame.at<uchar>(result.y, result.x);
            //std::cout << "Color value: " << colorValue << endl;
        }
        
        // Calculate the average color value for the current row
        totalColorValue += colorValue / MYLENGTH10;
        //std::cout << "Total color value: " << totalColorValue << endl;
        
        // Reset the color value for the next row
        colorValue = 0;
    }
    
    // Calculate the average color value for the entire cube and store it in the 'colorValues' array
    colorValues[pos] = totalColorValue / MYLENGTH10;
    //std::cout << "passed check result matches end" << std::endl;
    
    return 0;
}

int Camera::get_color_value_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture& cap) {
    // Capture a frame from the video using the video capture 'cap'
    cv::Mat frame;
    cap.read(frame);

    // Convert the captured frame to grayscale
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    int colorValue = 0;
    int totalColorValue = 0;
    
    // Iterate over the cube's region of interest
    for (int i = 0; i < MYLENGTH10; i++) {
        MyPoint result;
        result.y = start.y + i;

        for (int j = 0; j < MYLENGTH10; j++) {
            result.x = start.x + j;

            // Accumulate the color value at the current pixel location
            colorValue += grayFrame.at<uchar>(result.y, result.x);
        }
        
        // Calculate the average color value for the current row
        totalColorValue += colorValue / MYLENGTH10;
        colorValue = 0;
    }
    
    // Calculate and return the average color value for the entire cube
    return totalColorValue / MYLENGTH10;
}

void Camera::color_cube_pixels(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture& cap, cv::Mat& coloredFrame) {
    // Capture a frame from the video using the video capture 'cap'
    cv::Mat frame;
    cap.read(frame);

    // Iterate over the cube's region of interest
    for (int i = 0; i < MYLENGTH10; i++) {
        MyPoint result;
        result.y = start.y + i;

        for (int j = 0; j < MYLENGTH10; j++) {
            result.x = start.x + j;

            // Set the color value of the pixel to a specific color
            coloredFrame.at<cv::Vec3b>(result.y, result.x) = cv::Vec3b(0, 0, 255);  // Blue color (BGR format)
        }
    }
}

int Camera::view_frame() {
    // Set up the camera capture
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;

    while (true) {
        // Read a frame from the video capture
        cap.read(frame);

        // Check if the frame is empty
        if (frame.empty()) {
            std::cout << "empty frame" << std::endl;
            break;
        }

        // Display the frame in a window named "Frame"
        cv::imshow("Frame", frame);

        // Wait for a key press for 1 millisecond
        // If the pressed key is the escape key (key code 27), exit the loop
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // Release the camera capture and close all windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

int Camera::take_picture(){
    cv::VideoCapture cap = setup_camera();

    // Check if the camera is opened successfully
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera!" << std::endl;
        return -1;
    }

    int i = 0;
    while (true)
    {
        cv::Mat frame;
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty())
        {
            std::cerr << "Failed to capture frame!" << std::endl;
            break;
        }

        // Display the camera feed in a window named "Camera Feed"
        cv::imshow("Camera Feed", frame);

        // Wait for a key press for 1 millisecond
        char key = cv::waitKey(1);
     
        if (key == ' ')
        {
            // Capture a picture when the spacebar is pressed

            MyPoint start, end;
            cv::Mat coloredFrame = frame.clone(); // Create a clone of the frame

            // Color the pixels of the cube's regions of interest in the cloned frame
            for (int i = 0; i < (sizeof(startPosY) / sizeof(startPosY[0])); i++) {
                start.x = line1;
                start.y = startPosY[i];
                end.x = start.x + 9;
                end.y = start.y + 9;
                color_cube_pixels(start, end, i, cap, coloredFrame);
            }
            
            for (int i = 0; i < (sizeof(startPosY) / sizeof(startPosY[0])); i++) {
                start.x = line2;
                start.y = startPosY[i];
                end.x = start.x + 9;
                end.y = start.y + 9;
                color_cube_pixels(start, end, i + 22, cap, coloredFrame);
            }
            
            for (int i = 0; i < (sizeof(startPosX) / sizeof(startPosX[0])); i++) {
                start.x = startPosX[i];
                start.y = 130;
                end.x = line2 - 1;
                end.y = start.y + 9;
                color_cube_pixels(start, end, i + 44, cap, coloredFrame);
            }

            // Save the colored frame as an image
            std::string filename = "test_pictures/test_borders_pic" + std::to_string(i) + ".jpg";
            cv::imwrite(filename, coloredFrame);
            std::cout << "Image captured and saved as " << filename << std::endl;
            i++;
        }
        else if (key == 27) // ASCII code for ESC
        {
            break;
        }
    }

    // Release the camera capture and close all windows
    cap.release();
    cv::destroyAllWindows();
    return 0;
}

int Camera::take_mono_picture(){
    cv::VideoCapture cap = setup_camera();

    // Check if the camera is opened successfully
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera!" << std::endl;
        return -1;
    }

    int i = 0;
    while (true)
    {
        cv::Mat frame;
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty())
        {
            std::cerr << "Failed to capture frame!" << std::endl;
            break;
        }

        // Display the camera feed in a window named "Camera Feed"
        cv::imshow("Camera Feed", frame);

        // Convert the captured frame to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Wait for a key press for 1 millisecond
        char key = cv::waitKey(1);
     
        if (key == ' ')
        {
            // Capture a monochrome picture when the spacebar is pressed

            std::string filename = "test_pictures/test_taking_a_mono_picture_" + std::to_string(i) + ".jpg";
            cv::imwrite(filename, grayFrame);
            std::cout << "Image captured and saved as " << filename << std::endl;
            i++;
        }
        else if (key == 27) // ASCII code for ESC
        {
            break;
        }
    }

    // Release the camera capture and close all windows
    cap.release();
    cv::destroyAllWindows();
    return 0;
}




