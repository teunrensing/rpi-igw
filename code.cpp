#include <iostream>
#include <vector>
#include <cmath>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

// Constants for the HOG algorithm
const int WINDOW_WIDTH = 64;
const int WINDOW_HEIGHT = 128;
const int BLOCK_WIDTH = 16;
const int BLOCK_HEIGHT = 16;
const int CELL_WIDTH = 8;
const int CELL_HEIGHT = 8;
const int NBINS = 9;

// Structure for representing a person
struct Person {
    int x;
    int y;
    int width;
    int height;
};

// Function for computing the HOG descriptor of an image patch
void computeHOGDescriptor(const unsigned char* image, int width, int height, vector<float>& descriptor) {
    // Initialize the parameters for the HOG algorithm
    int block_width = BLOCK_WIDTH;
    int block_height = BLOCK_HEIGHT;
    int cell_width = CELL_WIDTH;
    int cell_height = CELL_HEIGHT;
    int nbins = NBINS;

    // Compute the gradient of the image using the Sobel operator
    vector<float> gx(width*height, 0), gy(width*height, 0);
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            int k = i*width+j;
            gx[k] = image[k+1] - image[k-1];
            gy[k] = image[k+width] - image[k-width];
        }
    }

    // Compute the magnitude and orientation of the gradient
    vector<float> magnitude(width*height, 0), orientation(width*height, 0);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int k = i*width+j;
            magnitude[k] = sqrt(gx[k]*gx[k] + gy[k]*gy[k]);
            orientation[k] = atan2(gy[k], gx[k]);
            if (orientation[k] < 0) {
                orientation[k] += 2*M_PI;
            }
        }
    }

    // Compute the HOG descriptor of each block
    int ncells_x = block_width / cell_width;
    int ncells_y = block_height / cell_height;
    descriptor.resize(ncells_x * ncells_y * nbins);
    for (int i = 0; i < ncells_x; i++) {
        for (int j = 0; j < ncells_y; j++) {
            vector<float> cell_magnitude(cell_width*cell_height, 0), cell_orientation(cell_width*cell_height, 0);
            for (int u = 0; u < cell_width; u++) {
                for (int v = 0; v < cell_height; v++) {
                    int k = (j*cell_height+v)*width + i*cell_width+u;
                    cell_magnitude[v*cell_width+u] = magnitude[k];
                    cell_orientation[v*cell_width+u] = orientation[k];
                }
            }

            // Compute the histogram of orientations in the cell
            vector<float> hist(nbins, 0);
            for (int u = 0; u < cell_width; u++) {
                for (int v = 0; v < cell_height; v++) {
                   
                int k = v*cell_width+u;
                float o = cell_orientation[k];
                int bin = (int)(o / (2*M_PI/nbins));
                float d = (o - bin*(2*M_PI/nbins)) / (2*M_PI/nbins);
                hist[bin] += cell_magnitude[k] * (1-d);
                if (bin < nbins-1) {
                    hist[bin+1] += cell_magnitude[k] * d;
                } else {
                    hist[0] += cell_magnitude[k] * d;
                }
            }
        }

        // Normalize the histogram by L2 norm
        float norm = 0;
        for (int k = 0; k < nbins; k++) {
            norm += hist[k]*hist[k];
        }
        norm = sqrt(norm);
        if (norm > 1e-6) {
            for (int k = 0; k < nbins; k++) {
                hist[k] /= norm;
            }
        }

        // Add the histogram to the HOG descriptor of the block
        for (int k = 0; k < nbins; k++) {
            descriptor[(j*ncells_x+i)*nbins+k] = hist[k];
        }
    }
}
// Compute the HOG descriptor of the image
vector<float> descriptor;
computeHOGDescriptor(image, width, height, descriptor);

// Compute the HOG descriptor of each window and classify it as person or not
vector<Person> people;
for (int i = 0; i < height-window_height; i += 4) {
    for (int j = 0; j < width-window_width; j += 4) {
        vector<float> window_descriptor(descriptor.begin() + i*width/CELL_HEIGHT + j/CELL_WIDTH, descriptor.begin() + (i+window_height)/CELL_HEIGHT*width + (j+window_width)/CELL_WIDTH);
        float score = 0;
        for (int k = 0; k < window_descriptor.size(); k++) {
            score += window_descriptor[k];
        }
        if (score > threshold*window_descriptor.size()) {
            people.push_back({j, i, window_width, window_height});
        }
    }
}

return people;
// Initialize the USB camera
struct v4l2_capability cap;
struct v4l2_format fmt;
struct v4l2_requestbuffers req;
struct v4l2_buffer buf;
memset(&cap, 0, sizeof(cap));
memset(&fmt, 0, sizeof(fmt));
memset(&req, 0, sizeof(req));
memset(&buf, 0, sizeof(buf));
if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
    cerr << "Error: cannot query USB camera capabilities." << endl;
    return 1;
}
if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
    cerr << "Error: USB camera does not support video capture." << endl;
    return 1;
}
if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
    cerr << "Error: USB camera does not support streaming I/O." << endl;
    return 1;
}
fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
fmt.fmt.pix.width = CAMERA_WIDTH;
fmt.fmt.pix.height = CAMERA_HEIGHT;
fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
fmt.fmt.pix.field = V4L2_FIELD_NONE;
if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
    cerr << "Error: cannot set USB camera format." << endl;
    return 1;
}
req.count = 1;
req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
req.memory = V4L2_MEMORY_MMAP;
if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
    cerr << "Error: cannot request USB camera buffer." << endl;
    return 1;
}
void* buffer = mmap(NULL, fmt.fmt.pix.sizeimage, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (buffer == MAP_FAILED) {
    cerr << "Error: cannot map USB camera buffer." << endl;
    return 1;
}
buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
buf.memory = V4L2_MEMORY_MMAP;
buf.index = 0;
if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
    cerr << "Error: cannot enqueue USB camera buffer." << endl;
    return 1;
}
if (ioctl(fd, VIDIOC_STREAMON, &buf.type) == -1) {
    cerr << "Error: cannot start USB camera streaming." << endl;
    return 1;
}

// Initialize the window for displaying the image and the people detection results
namedWindow("Camera", WINDOW_AUTOSIZE);
namedWindow("People", WINDOW_AUTOSIZE);

// Main loop for reading the image from the USB camera and detecting people in it
while (waitKey(1) != 'q') {
    // Read the image from the USB camera
    if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) {
        cerr << "Error: cannot dequeue USB camera buffer." << endl;
        continue;
    }
    Mat frame(CAMERA_HEIGHT, CAMERA_WIDTH, CV_8UC2, buffer);
    cvtColor(frame, frame, COLOR_YUV2BGR_YUYV);
    flip(frame, frame, 1);
    imshow("Camera", frame);

    // Detect people in the image
    vector<Person> people = detectPeople(frame.data, frame.cols, frame.rows);

    // Draw rectangles around the detected people
    Mat people_image = frame.clone();
    for (int i = 0; i < people.size(); i++) {
        rectangle(people_image, Rect(people[i].x, people[i].y, people[i].width, people[i].height), Scalar(0, 255, 0), 2);
    }
    imshow("People", people_image);
}

// Stop the USB camera streaming
if (ioctl(fd, VIDIOC_STREAMOFF, &buf.type) == -1) {
    cerr << "Error: cannot stop USB camera streaming." << endl;
    return 1;
}

// Close the USB camera
close(fd);

return 0;
// Iterate over the image by sliding a window of fixed size
for (int y = 0; y <= image_height - WINDOW_SIZE; y += WINDOW_STEP) {
    for (int x = 0; x <= image_width - WINDOW_SIZE; x += WINDOW_STEP) {
        // Extract the image patch corresponding to the current window
        Mat patch(WINDOW_SIZE, WINDOW_SIZE, CV_8UC3);
        for (int dy = 0; dy < WINDOW_SIZE; dy++) {
            for (int dx = 0; dx < WINDOW_SIZE; dx++) {
                int i = (y + dy) * image_width + (x + dx) * 2;
                patch.at<Vec3b>(dy, dx) = Vec3b(image_data[i + 1], image_data[i], image_data[i + 2]);
            }
        }

        // Compute the HOG feature vector for the image patch
        Mat hog_descriptor;
        HOGDescriptor hog(Size(WINDOW_SIZE, WINDOW_SIZE), Size(BLOCK_SIZE, BLOCK_SIZE), Size(BLOCK_STRIDE, BLOCK_STRIDE), Size(CELL_SIZE, CELL_SIZE), NBINS);
        hog.compute(patch, hog_descriptor);

        // Predict whether the image patch contains a person using the SVM classifier
        float prediction = svm.predict(hog_descriptor);
        if (prediction > 0) {
            people.push_back(Person(x, y, WINDOW_SIZE, WINDOW_SIZE));
        }
    }
}

return people;
// Set the camera resolution
cap.set(CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
cap.set(CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);

// Load the SVM classifier
SVM svm;
svm.load(SVM_MODEL_FILE);

while (true) {
    // Read a frame from the camera
    Mat frame;
    cap >> frame;
    if (frame.empty()) {
        cerr << "Error reading frame from camera" << endl;
        break;
    }

    // Convert the image to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Detect people in the image
    vector<Person> people = detectPeople(gray.data, gray.cols, gray.rows);

    // Draw bounding boxes around detected people
    drawPeople(frame, people);

    // Show the image
    imshow("Camera", frame);

    // Exit the program if the user presses the 'q' key
    if (waitKey(1) == 'q') {
        break;
    }
}

// Release the camera and close the window
cap.release();
destroyAllWindows();

return 0;
