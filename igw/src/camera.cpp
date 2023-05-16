#include "camera.hpp"

Camera::Camera() : maxY(360), maxX(640), line1(maxX / 3), line2(maxX / 3 * 2) {
    // Constructor implementation
}

Camera::~Camera() {
    // Destructor implementation
}

cv::VideoCapture Camera::setup_camera() {
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, maxX);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, maxY);
    //cap.set(cv::CAP_PROP_FPS, cap.get(cv::CAP_PROP_FPS) * 0.5);

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

MyPoint Camera::get_values_point(MyPoint p1) {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap.read(frame);
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    p1.colorValue = grayFrame.at<uchar>(p1.y, p1.x);
    return p1;
}

int Camera::get_color_value_cube(MyPoint start, MyPoint end) {
    // Function implementation
    return 0;
}

int Camera::callibrate() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    cap >> frame;

    int** result = get_measurements_points();
    for (int i = 0; i < maxY / 2; i++) {
        for (int j = 0; j < sizeof(result[i]); j++) {
            // Process the result array
        }
    }

    // Deallocate the dynamically allocated memory
    for (int j = 0; j < maxY / 2; j++) {
        delete[] result[j];
    }
    delete[] result;

    return 1;
}

int** Camera::get_measurements_points() {
    int** gray_array = new int*[2];
    for (int x = 0; x < 2; x++) {
        gray_array[x] = new int[maxY];
    }

    // maybe use multithreading to make it more efficient?
    for (int y = 0; y < maxY; y++) {
        //gray_array[0][y] = get_values_point( line1, y );
        //gray_array[1][y] = get_values_point( line2, y );
    }

    return gray_array;
}

int Camera::view_frame() {
    cv::VideoCapture cap = setup_camera();
    cv::Mat frame;
    // callibrate();

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            break;
        }
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        //std::cout << "frame width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << " frame height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";

        // if get new frame renew parameters max width and height.
        //cv::Point pt1(cap.get(cv::CAP_PROP_FRAME_WIDTH), 200); // start point
        //cv::Point pt2(100, cap.get(cv::CAP_PROP_FRAME_HEIGHT)); // end point
        //cv::Scalar color //green
        //cv::line(grayFrame, pt1, pt2, color, 2);

        cv::imshow("GrayFrame", grayFrame);
        if (cv::waitKey(1) == 27) {
            break;
        }
}
cap.release();
cv::destroyAllWindows();
return 0;
}
