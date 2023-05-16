#include <opencv2/opencv.hpp>
#include "camera.hpp"
int main() {
    Camera cam;
    
    cam.setup_camera();
    cam.view_frame();
    return 0;
}

