#include <opencv2/opencv.hpp>
#include "camera.hpp"
int main() {
    Camera cam;
    
    cam.setup_camera();
    cam.calibrate();
    cam.take_picture();
    return 0;
}

