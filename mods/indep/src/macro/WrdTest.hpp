#pragma once

#define WRD_DEF_TEST(cls) \
    WRD_DEF_THIS_1(cls) \
    class WRD_CONCAT(cls, Test); \
    typedef WRD_CONCAT(cls, Test) ThisTest;
