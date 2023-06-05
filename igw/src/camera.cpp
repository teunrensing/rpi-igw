#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

int startPosX[]={210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410};
int startPosY[]={130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350};

Camera::Camera() : maxY(360), maxX(640), line1(210), line2(410) {
    
}

Camera::~Camera() {
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

void Camera::calibrate() {
    // std::cout << "start calibrate" << std::endl;
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    MyPoint start, end;
     if (frame.empty()) {
            std::cout << "empty frame" << std::endl;
        }
       
    for(int i=0;i<(sizeof(startPosY)/sizeof(startPosY[0]));i++){
        start.x = line1;
        start.y =startPosY[i];
        end.x = start.x +9;
        end.y= start.y +9;
        set_values_color_cube(start, end, i, cap);
    }
    for (int i = 0; i<(sizeof(startPosY)/sizeof(startPosY[0])); i++) {
        start.x = line2;
        start.y =startPosY[i];
        end.x = start.x +9;
        end.y= start.y +9;
        set_values_color_cube(start, end, i+23, cap);
    }

    for (int i = 0; i <(sizeof(startPosX)/sizeof(startPosX[0])); i++) {
        start.x = startPosX[i];
        start.y =130;
        end.x = line2-1;
        end.y= start.y +9;
        set_values_color_cube(start, end, i+46, cap);
    }
    cap.release();
    // std::cout <<"end calibrate"<<endl;
    
    
}
int Camera::detectChange(){
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    int sens = 20;
    const int range = 23;//(sizeof(startPosY)/sizeof(startPosY[0]));
    MyPoint start, end;
     if (frame.empty()) {
            std::cout << "empty frame" << std::endl;
        }
       
    for(int i=0;i<range;i++){
        start.x = line1;
        start.y =startPosY[i];
        end.x = start.x +9;
        end.y= start.y +9;
        int currentValue = get_color_value_cube(start, end, i, cap);
        if(( currentValue-colorValues[i]) < -sens ||(currentValue -colorValues[i]) > sens){
            detectedCounter++;
            detectedLeft = true;
            std::cout<< "Current value: "<< currentValue<< " Default value: "<< colorValues[i]<<" Print i: "<< i<< endl;
            std::cout<<"Detected a change at the left, the total changes detected are: "<< detectedCounter<< endl;
            break;
        }else{
            
        }
    }
    for (int i = 0; i<range; i++) {
        start.x = line2;
        start.y =startPosY[i];
        end.x = start.x +9;
        end.y= start.y +9;
        int currentValue = get_color_value_cube(start, end, i+range, cap);
        if((currentValue -colorValues[i+range]) < -sens ||(currentValue-colorValues[i+range]) > sens){
            detectedCounter++;
            detectedRight = true;
            std::cout<< "Current value: "<< currentValue<< " Default value: "<< colorValues[i+range]<<" Print i: "<< i+range<< endl;
            std::cout<<"Detected a change at the right, the total changes detected are: "<< detectedCounter<< endl;
            break;
        }else{
       
        }
    }

    for (int i = 0; i <(sizeof(startPosX)/sizeof(startPosX[0])); i++) {
        start.x = startPosX[i];1
        start.y =130;
        end.x = line2-1;
        end.y= start.y +9;
        int currentValue = get_color_value_cube(start, end, i+range*2, cap);
        if((currentValue -colorValues[i+range*2]) < -sens ||(currentValue -colorValues[i+range*2]) > sens){
            detectedCounter++;
            detectedMiddle = true;
            std::cout<< "Current value: "<< currentValue<< " Default value: "<< colorValues[i+range*2]<<" Print i: "<< i+range*2<< endl;
            std::cout<<"Detected a change at the middle, the total changes detected are: "<< detectedCounter<< endl;
            break;
        }else{
        
        }
    }
    cap.release();
    return 0;
}
/*
cv::Mat Camera::get_gray_values_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap.read(frame);
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    //p1.colorValue = grayFrame.at<uchar>(p1.y, p1.x);
    return grayFrame;
}*/

int Camera::set_values_color_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture&  cap) {
        //std::cout << "start cube" << std::endl;
        cv::Mat frame;
        cap.read(frame);
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        int colorValue = 0;
        int totalColorValue = 0;
        
        for (int i = 0; i < MYLENGTH10; i++) {
            MyPoint result;
            result.y = start.y + i;

            /*if (result.y != end.y - (MYLENGTH10 - i)) {
                std::cout << "y values of result and end don't match" << std::endl;
                std::cout << "result.y: " << result.y << ", expected: " << end.y + (MYLENGTH10 - i) << std::endl;
                return -1;
            }*/

            for (int j = 0; j < MYLENGTH10; j++) {
                result.x = start.x + j;

                /*if (result.x != end.x - (MYLENGTH10 - j)) {
                    std::cout << "x values of result and end don't match" << std::endl;
                    std::cout << "result.x: " << result.x << ", expected: " << end.x - (MYLENGTH10 - j) << std::endl;
                    return -1;
                }*/

                colorValue += grayFrame.at<uchar>(result.y,result.x);
                //std::cout <<"Color value: "<< colorValue << endl;
            }
            totalColorValue += colorValue/MYLENGTH10;
            //std::cout <<"Total color value: "<< totalColorValue << endl;           
            colorValue=0;
        }
        colorValues[pos] = totalColorValue/MYLENGTH10;
       // std::cout << "passed check result matches end" << std::endl;
        return 0;
}
int Camera::get_color_value_cube(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture&  cap) {
        //std::cout << "start cube" << std::endl;
        cv::Mat frame;
        cap.read(frame);
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        int colorValue = 0;
        int totalColorValue = 0;
        
        for (int i = 0; i < MYLENGTH10; i++) {
            MyPoint result;
            result.y = start.y + i;


            for (int j = 0; j < MYLENGTH10; j++) {
                result.x = start.x + j;
                colorValue += grayFrame.at<uchar>(result.y,result.x);
            }
            totalColorValue += colorValue/MYLENGTH10;
            colorValue=0;
        }
        
        return  totalColorValue/MYLENGTH10;
}

void Camera::color_cube_pixels(const MyPoint& start, const MyPoint& end, int pos, cv::VideoCapture& cap ,cv::Mat& coloredFrame) {
    cv::Mat frame;
    cap.read(frame);

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
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            std::cout << "empty frame" << std::endl;
            break;
        }
        

        cv::imshow("Frame", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}


int Camera::take_picture(){
   cv::VideoCapture cap = setup_camera();
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera!" << std::endl;
        return -1;
    }
    int i =0;
    while (true)
    {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
        {
            std::cerr << "Failed to capture frame!" << std::endl;
            break;
        }

        cv::imshow("Camera Feed", frame);         
        char key = cv::waitKey(1);
     
        if (key == ' '){   
            MyPoint start, end;
            cv::Mat coloredFrame = frame.clone(); // Create a clone of the frame
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

    cap.release();
    cv::destroyAllWindows();
    return 0;
  
}


int Camera::take_mono_picture(){
   cv::VideoCapture cap = setup_camera();
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open camera!" << std::endl;
        return -1;
    }

    int i =0;
    while (true)
    {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
        {
            std::cerr << "Failed to capture frame!" << std::endl;
            break;
        }

        cv::imshow("Camera Feed", frame);
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        char key = cv::waitKey(1);
     
        if (key == ' ')
        {
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

    cap.release();
    cv::destroyAllWindows();
    return 0;
  
}



