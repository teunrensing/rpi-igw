# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aih/Desktop/igw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aih/Desktop/igw/build

# Include any dependencies generated for this target.
include CMakeFiles/igw_v1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/igw_v1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/igw_v1.dir/flags.make

CMakeFiles/igw_v1.dir/src/main.cpp.o: CMakeFiles/igw_v1.dir/flags.make
CMakeFiles/igw_v1.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aih/Desktop/igw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/igw_v1.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/igw_v1.dir/src/main.cpp.o -c /home/aih/Desktop/igw/src/main.cpp

CMakeFiles/igw_v1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/igw_v1.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aih/Desktop/igw/src/main.cpp > CMakeFiles/igw_v1.dir/src/main.cpp.i

CMakeFiles/igw_v1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/igw_v1.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aih/Desktop/igw/src/main.cpp -o CMakeFiles/igw_v1.dir/src/main.cpp.s

CMakeFiles/igw_v1.dir/src/camera.cpp.o: CMakeFiles/igw_v1.dir/flags.make
CMakeFiles/igw_v1.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aih/Desktop/igw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/igw_v1.dir/src/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/igw_v1.dir/src/camera.cpp.o -c /home/aih/Desktop/igw/src/camera.cpp

CMakeFiles/igw_v1.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/igw_v1.dir/src/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aih/Desktop/igw/src/camera.cpp > CMakeFiles/igw_v1.dir/src/camera.cpp.i

CMakeFiles/igw_v1.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/igw_v1.dir/src/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aih/Desktop/igw/src/camera.cpp -o CMakeFiles/igw_v1.dir/src/camera.cpp.s

CMakeFiles/igw_v1.dir/src/line.cpp.o: CMakeFiles/igw_v1.dir/flags.make
CMakeFiles/igw_v1.dir/src/line.cpp.o: ../src/line.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aih/Desktop/igw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/igw_v1.dir/src/line.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/igw_v1.dir/src/line.cpp.o -c /home/aih/Desktop/igw/src/line.cpp

CMakeFiles/igw_v1.dir/src/line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/igw_v1.dir/src/line.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aih/Desktop/igw/src/line.cpp > CMakeFiles/igw_v1.dir/src/line.cpp.i

CMakeFiles/igw_v1.dir/src/line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/igw_v1.dir/src/line.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aih/Desktop/igw/src/line.cpp -o CMakeFiles/igw_v1.dir/src/line.cpp.s

# Object files for target igw_v1
igw_v1_OBJECTS = \
"CMakeFiles/igw_v1.dir/src/main.cpp.o" \
"CMakeFiles/igw_v1.dir/src/camera.cpp.o" \
"CMakeFiles/igw_v1.dir/src/line.cpp.o"

# External object files for target igw_v1
igw_v1_EXTERNAL_OBJECTS =

igw_v1: CMakeFiles/igw_v1.dir/src/main.cpp.o
igw_v1: CMakeFiles/igw_v1.dir/src/camera.cpp.o
igw_v1: CMakeFiles/igw_v1.dir/src/line.cpp.o
igw_v1: CMakeFiles/igw_v1.dir/build.make
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_gapi.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_highgui.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_ml.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_objdetect.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_photo.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_stitching.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_video.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_videoio.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_imgcodecs.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_dnn.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_calib3d.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_features2d.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_flann.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_imgproc.so.4.7.0
igw_v1: /usr/local/lib/arm-linux-gnueabihf/libopencv_core.so.4.7.0
igw_v1: CMakeFiles/igw_v1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aih/Desktop/igw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable igw_v1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/igw_v1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/igw_v1.dir/build: igw_v1

.PHONY : CMakeFiles/igw_v1.dir/build

CMakeFiles/igw_v1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/igw_v1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/igw_v1.dir/clean

CMakeFiles/igw_v1.dir/depend:
	cd /home/aih/Desktop/igw/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aih/Desktop/igw /home/aih/Desktop/igw /home/aih/Desktop/igw/build /home/aih/Desktop/igw/build /home/aih/Desktop/igw/build/CMakeFiles/igw_v1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/igw_v1.dir/depend
