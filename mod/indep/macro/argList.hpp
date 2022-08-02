#pragma once

#include "overload.hpp"

//  TODO: improve this using some NAMU_EACH.
#define NAMU_LIST_PAIR_X_2(x1, y1)   x1
#define NAMU_LIST_PAIR_X_4(x1, y1, x2, y2)   x1, x2
#define NAMU_LIST_PAIR_X_6(x1, y1, x2, y2, x3, y3)   x1, x2, x3
#define NAMU_LIST_PAIR_X_8(x1, y1, x2, y2, x3, y3, x4, y4)   x1, x2, x3, x4
#define NAMU_LIST_PAIR_X_10(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)  x1, x2, x3, x4, x5
#define NAMU_LIST_PAIR_X(...)    NAMU_OVERLOAD(NAMU_LIST_PAIR_X, __VA_ARGS__)

#define NAMU_LIST_PAIR_Y_2(x1, y1)   y1
#define NAMU_LIST_PAIR_Y_4(x1, y1, x2, y2)   y1, y2
#define NAMU_LIST_PAIR_Y_6(x1, y1, x2, y2, x3, y3)   y1, y2, y3
#define NAMU_LIST_PAIR_Y_8(x1, y1, x2, y2, x3, y3, x4, y4)   y1, y2, y3, y4
#define NAMU_LIST_PAIR_Y_10(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5)  y1, y2, y3, y4, y5
#define NAMU_LIST_PAIR_Y(...)    NAMU_OVERLOAD(NAMU_LIST_PAIR_Y, __VA_ARGS__)

