#include <opencv2/opencv.hpp>
#include "camera.hpp"
int main() {
    Camera cam;
    cam.calibrate();
    while(1){
        cam.detectChange();
    }
    
    std::cout << "END__________________________________________________";
    return 0;
}

