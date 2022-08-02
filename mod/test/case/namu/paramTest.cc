#include "../../common/dep.hpp"

using namespace namu;
using namespace std;

namespace {
    struct myObj : public obj {
        WRD(CLASS(myObj, obj))

    public:
        myObj(int newVal = 0): val(newVal) {}

        int val;

        wbool _onSame(const typeProvidable& rhs) const override {
            const myObj& cast = (const myObj&) rhs;
            return val == cast.val;
        }
    };
}

/*TEST(paramTest, testParamOrigin) {
    myObj obj1;
    param p1("hello", obj1);
    param p2("world", obj1.getType());

    ASSERT_EQ(p1.getOrigin().getType(), obj1.getType());
    ASSERT_EQ(p1.getOrigin()->getType(), obj1.getType());
    ASSERT_EQ(p2.getOrigin().getType(), obj1.getType());

    p1.setOrigin(wInt().getType());
    ASSERT_EQ(p1.getType(), ttype<wInt>::get());
    ASSERT_TRUE(nul(*p1.getOrigin()));
}*/
