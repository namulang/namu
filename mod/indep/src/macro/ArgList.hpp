#pragma once

#include "overload.hpp"

//  TODO: improve this using some WRD_EACH.
#define WRD_LIST_PAIR_X_2(x1, y1)   x1
#define WRD_LIST_PAIR_X_4(x1, y1, x2, y2)   x1, x2
#define WRD_LIST_PAIR_X_6(x1, y1, x2, y2, x3, y3)   x1, x2, x3
#define WRD_LIST_PAIR_X_8(x1, y1, x2, y2, x3, y3, x4, y4)   x1, x2, x3, x4
#define WRD_LIST_PAIR_X_10(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)  x1, x2, x3, x4, x5
#define WRD_LIST_PAIR_X(...)    WRD_OVERLOAD(WRD_LIST_PAIR_X, __VA_ARGS__)

#define WRD_LIST_PAIR_Y_2(x1, y1)   y1
#define WRD_LIST_PAIR_Y_4(x1, y1, x2, y2)   y1, y2
#define WRD_LIST_PAIR_Y_6(x1, y1, x2, y2, x3, y3)   y1, y2, y3
#define WRD_LIST_PAIR_Y_8(x1, y1, x2, y2, x3, y3, x4, y4)   y1, y2, y3, y4
#define WRD_LIST_PAIR_Y_10(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)  y1, y2, y3, y4, y5
#define WRD_LIST_PAIR_Y(...)    WRD_OVERLOAD(WRD_LIST_PAIR_Y, __VA_ARGS__)

