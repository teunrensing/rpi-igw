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


cv::Mat Camera::get_gray_values_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap.read(frame);
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    //p1.colorValue = grayFrame.at<uchar>(p1.y, p1.x);
    return grayFrame;
}
int Camera::set_values_cube(MyPoint start, MyPoint end, int pos) {
    std::cout << "start cube" << std::endl;
    MyPoint result;

    for (int i = 0; i < MYLENGTH10; i++)
    {
        result.y = start.y + i;
        if (result.y != end.y - (MYLENGTH10 - i))
        {
            std::cout << "y values of result and end don't match" << std::endl;
            std::cout << "result.y: " << result.y << ", expected: " << end.y + (MYLENGTH10 - i) << std::endl;
             return -1;
        }
        
        for (int j = 0; j < MYLENGTH10; j++)
        {
          
            result.x = start.x + j;

            if (result.x != end.x - (MYLENGTH10 - j))
            {
                std::cout << "x values of result and end don't match" << std::endl;
                std::cout << "result.x: " << result.x << ", expected: " << end.x - (MYLENGTH10 - j) << std::endl;
                return -1;
            }
         
            array_[pos][i][j] = result;
        }

    }
    std::cout << "passed check result matches end" << std::endl;
    return 0;
  
}

int Camera::calibrate() {
    MyPoint lt,rt,lb,rb;
   // std::cout << "start calibrate" << std::endl;
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
 /*   
        start.x =line1;
        start.y=(maxY-10);
        end.x=line1+10;
        end.y=maxY;
        set_values_cube(start,end,0);
*/
try {
    for(int i = 0; i < 13; i++) {
        std::cout << "Loop iteration: " << i << std::endl;
        start.x = line1;
        start.y = (maxY - 10) - 10 * i;
        end.x = line1 + 10;
        end.y = maxY - 10 * i;
        set_values_cube(start, end, i);
    }
} catch (const std::exception& e) {
    std::cout << "An exception occurred: " << e.what() << std::endl;
}

    /*for(int i=0; i<1;i++){
        start.x =line1;
        start.y=(maxY-10)-10*i;
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
    }*/
   // std::cout <<"end calibrate"<<endl;
    return 0;
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
        //cv::rectangle(frame, cv::Point(1, 1), cv::Point(10, 10), cv::Scalar(0, 255, 0), 2);//drawing a rectangle
         
        char key = cv::waitKey(1);
     
        if (key == ' ')
        {   
            for(int x=0; x< 3;x++){
                for(int y=0; y< MYLENGTH10 ;y++){
                    for(int z=0; z<MYLENGTH10;z++){
                        MyPoint r = array_[x][y][z];
                        frame.at<cv::Vec3b>(r.y, r.x) = cv::Vec3b(0, 0, 255);// set pixel red
                    }
                }
            }
            std::string filename = "test_pictures/test_color_pic" + std::to_string(i) + ".jpg";
            cv::imwrite(filename, frame);
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
