#include "../../wrdTest.hpp"

using namespace wrd;
using namespace std;

struct objTest : public wrdTest {};

namespace {
    struct myObj : public obj {
        WRD(CLASS(myObj, obj))
    };
}

TEST_F(objTest, testGetOriginPointingThis) {
    myObj obj1;
    ASSERT_FALSE(nul(obj1.getOrigin()));
    ASSERT_EQ(&obj1.getOrigin(), &obj1);

    tstr<obj> copied(obj1.clone());
    ASSERT_TRUE(copied);
    ASSERT_NE(&copied.get(), &obj1);
}
