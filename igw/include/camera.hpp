#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "setup.hpp"

bool setup_camera();
int callibrate(int *mX, int *mY, int *l1, int *l2, int *p1rl1, int*p1rl2, int *p2rl1, int *p2rl2);
int get_measurements_point(int x, int y);
int get_measurements_points();
int view_frame(bool x);

#endif
