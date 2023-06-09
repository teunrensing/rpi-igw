# Rpi-4 vision project
This project started on: 21-3-2023 : 12.07

This repository contains a C++ codebase for a Raspberry Pi 4 vision project. The project aims to develop a camera system that allows interaction with a video capture device. It provides functionalities such as camera setup, color calibration, change detection, and image capture.

Please note that this project is currently a work in progress and may undergo further development and refinement.

### General Description

The provided code implements a camera system in C++ that allows interaction with a video capture device. It provides various functionalities such as camera setup, color calibration, change detection, and image capture.

The code allows you to set up the camera by configuring properties such as frame width and height. Once the camera is set up, you can perform color calibration for different regions of interest within the camera's frame. This calibration process helps determine the average color values of specific areas.

After calibration, the code enables you to monitor the camera feed for changes in the color values of the calibrated areas. It compares the current color values with the calibrated values and detects changes based on predefined sensitivity thresholds.

Additionally, the code provides functionalities for capturing frames from the camera. You can view the camera's live feed in a window and capture still images. There is an option to capture both color and monochrome (black and white) images.

Overall, this code offers a framework for camera interaction and manipulation. It can be utilized in various applications that require camera functionality, such as computer vision projects, robotics, surveillance systems, and more.

### Class Diagram

The class diagram illustrates the relationships and attributes of the classes involved in the system:

```
                 +----------------------+
                 |       Camera         |
                 +----------------------+
                 | - colorValues[]      |
                 | - detectedCounter    |
                 | - detectedRight      |
                 | - detectedMiddle     |
                 | - detectedLeft       |
                 | - maxY               |
                 | - maxX               |
                 | - line1              |
                 | - line2              |
                 +----------------------+
                           |
                           |
                           |
              +------------------------+
              |        MyPoint         |
              +------------------------+
              | - x                    |
              | - y                    |
              | - colorValue           |
              +------------------------+
                           |
                           |
                           |
              +------------------------+
              |      cv::VideoCapture  |
              +------------------------+
              | - Frame width          |
              | - Frame height         |
              +------------------------+
                           |
                           |
                           |
              +------------------------+
              |        cv::Mat         |
              +------------------------+
              | - Image data           |
              | - Color channels       |
              | - Image dimensions     |
              +------------------------+
```

The diagram represents a system that includes four classes: `Camera`, `MyPoint`, `cv::VideoCapture`, and `cv::Mat`.

- The `Camera` class represents a camera device and provides functionalities related to camera setup, calibration, change detection, and image capture. It has attributes such as `colorValues`, `detectedCounter`, `detectedRight`, `detectedMiddle`, `detectedLeft`, `maxY`, `maxX`, `line1`, and `line2`.
- The `MyPoint` class represents a point in the camera frame and contains attributes `x`, `y`, and `colorValue`.
- The `cv::VideoCapture` class represents a video capture device and provides access to video frames. It has attributes `Frame width` and `Frame height`.
- The `cv::Mat` class represents an image matrix and stores pixel data, color channels, and image dimensions.

### Camera Class Functions

The `Camera` class provides various functions for camera setup, calibration, frame analysis, and image capture. Here's

 an overview of the available functions:

- `Camera()`: Initializes a Camera object.
- `~Camera()`: Cleans up resources and destroys the Camera object.
- `setup_camera() -> cv::VideoCapture`: Sets up the camera by initializing a `cv::VideoCapture` object and returns it.
- `calibrate()`: Performs camera calibration.
- `detectChange() -> int`: Detects changes in the camera frame and returns an integer indicating the result.
- `set_values_color_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int`: Sets color values for a cube defined by two `MyPoint` objects, an integer, and a `cv::VideoCapture` object. Returns an integer indicating success or failure.
- `get_color_value_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int`: Retrieves the color value for a cube defined by two `MyPoint` objects, an integer, and a `cv::VideoCapture` object. Returns an integer indicating success or failure.
- `color_cube_pixels(const MyPoint&, const MyPoint&, int, cv::VideoCapture&, cv::Mat&) -> void`: Retrieves the color values of pixels within a cube defined by two `MyPoint` objects, an integer, a `cv::VideoCapture` object, and a `cv::Mat` object. Modifies the `cv::Mat` object with the pixel values.
- `view_frame() -> int`: Displays the camera frame and returns an integer indicating success or failure.
- `take_picture() -> int`: Takes a picture using the camera and returns an integer indicating success or failure.
- `take_mono_picture() -> int`: Takes a monochrome picture using the camera and returns an integer indicating success or failure.

Please refer to the source code for more details and implementation specifics.

---

You can use the provided information to create a detailed and informative README.md for your GitHub repository.
