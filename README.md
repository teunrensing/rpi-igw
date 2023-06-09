# Rpi-4 vision project
This project started on: 21-3-2023 : 12.07

This is a work in progress

# Genral Discription

The provided code implements a camera system in C++ that allows interaction with a video capture device. It provides various functionalities such as camera setup, color calibration, change detection, and image capture.

The code allows you to set up the camera by configuring properties such as frame width and height. Once the camera is set up, you can perform color calibration for different regions of interest within the camera's frame. This calibration process helps determine the average color values of specific areas.

After calibration, the code enables you to monitor the camera feed for changes in the color values of the calibrated areas. It compares the current color values with the calibrated values and detects changes based on predefined sensitivity thresholds.

Additionally, the code provides functionalities for capturing frames from the camera. You can view the camera's live feed in a window and capture still images. There is an option to capture both color and monochrome (black and white) images.

Overall, this code offers a framework for camera interaction and manipulation. It can be utilized in various applications that require camera functionality, such as computer vision projects, robotics, surveillance systems, and more.

# Class Diagram

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
The diagram represents a system that includes four classes: `Camera`, `MyPoint`, `cv::VideoCapture`, and `cv::Mat`.

`Camera` class:
- Attributes:
  - `colorValues[]`: An array to store color values.
  - `detectedCounter`: A counter for tracking the number of detected objects.
  - `detectedRight`: A variable to track the number of objects detected on the right side.
  - `detectedMiddle`: A variable to track the number of objects detected in the middle.
  - `detectedLeft`: A variable to track the number of objects detected on the left side.
  - `maxY`: Maximum Y-coordinate value.
  - `maxX`: Maximum X-coordinate value.
  - `line1`: Represents a line.
  - `line2`: Represents another line.

`MyPoint` class:
- Attributes:
  - `x`: X-coordinate value.
  - `y`: Y-coordinate value.
  - `colorValue`: Represents a color value.

`cv::VideoCapture` class:
- Attributes:
  - `Frame width`: Width of the captured video frame.
  - `Frame height`: Height of the captured video frame.

`cv::Mat` class:
- Attributes:
  - `Image data`: Represents the pixel data of an image.
  - `Color channels`: Indicates the number of color channels in the image (e.g., RGB or grayscale).
  - `Image dimensions`: Specifies the dimensions (width and height) of the image.

This diagram illustrates the relationships and attributes of the classes involved in the system. The `Camera` class uses instances of the `MyPoint` class to store and manipulate points. It also interacts with the `cv::VideoCapture` class, which represents a video capturing device, to obtain video frames. The `cv::Mat` class is used to handle image data, including the pixel values, color channels, and dimensions.   

# Function Diagram

+-----------------------------------------------------------------------------------------------+
|                                           Camera                                              |
+-----------------------------------------------------------------------------------------------+
|  -Camera()                                                                                     |
|  -~Camera()                                                                                    |
|  -setup_camera() -> cv::VideoCapture                                                           |
|  -calibrate()                                                                                  |
|  -detectChange() -> int                                                                        |
|  -set_values_color_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int         |
|  -get_color_value_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int          |
|  -color_cube_pixels(const MyPoint&, const MyPoint&, int, cv::VideoCapture&, cv::Mat&) -> void  |
|  -view_frame() -> int                                                                          |
|  -take_picture() -> int                                                                        |
|  -take_mono_picture() -> int                                                                   |
+-----------------------------------------------------------------------------------------------+
The `Camera` class represents a camera device and provides various functions for interacting with it. Here's a breakdown of the functions:

- `Camera()`: This is the constructor for the `Camera` class, used to create a new camera object.
- `~Camera()`: This is the destructor for the `Camera` class, responsible for cleaning up any resources associated with the camera object.

Camera setup and calibration:
- `setup_camera() -> cv::VideoCapture`: This function sets up the camera for capturing video frames and returns a `cv::VideoCapture` object that can be used for further operations.
- `calibrate()`: This function performs camera calibration, which involves estimating camera parameters to correct for lens distortions and other factors.

Change detection and color analysis:
- `detectChange() -> int`: This function detects changes in the camera frame and returns the number of detected changes.
- `set_values_color_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int`: This function sets the values for a color cube used in color analysis, taking two corner points, a side length, and a video capture object as parameters. It returns a status code indicating the success of the operation.
- `get_color_value_cube(const MyPoint&, const MyPoint&, int, cv::VideoCapture&) -> int`: This function retrieves the color value of the color cube, based on the provided corner points, side length, and video capture object. It returns a status code indicating the success of the operation.
- `color_cube_pixels(const MyPoint&, const MyPoint&, int, cv::VideoCapture&, cv::Mat&) -> void`: This function extracts the pixels within the color cube from the video frame, based on the provided corner points, side length, video capture object, and a matrix to store the extracted pixels.

Viewing and capturing frames:
- `view_frame() -> int`: This function displays the camera frame for viewing and returns a status code indicating the success of the operation.
- `take_picture() -> int`: This function captures a full-color picture using the camera and returns a status code indicating the success of the operation.
- `take_mono_picture() -> int`: This function captures a monochrome (black and white) picture using the camera and returns a status code indicating the success of the operation.

These functions provide a set of capabilities for interacting with a camera, including setup, calibration, change detection, color analysis, frame viewing, and picture capturing.
