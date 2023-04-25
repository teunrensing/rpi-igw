cmake_minimum_required(VERSION 3.5)
project(igw_v1)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Find OpenCV package and include directories
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the header and source files to the project
include_directories(include)
add_executable(igw_v1 src/main.cpp src/camera.cpp src/line.cpp)

# Link the OpenCV libraries to the project
target_link_libraries(igw_v1 ${OpenCV_LIBS})
