#include "../../common/dep.hpp"

using namespace namu;
using namespace std;

namespace {
    struct myObj : public obj {
        NAMU(CLASS(myObj, obj))

    public:
        myObj(int newVal = 0): val(newVal) {}

        int val;

        nbool _onSame(const typeProvidable& rhs) const override {
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

    p1.setOrigin(nInt().getType());
    ASSERT_EQ(p1.getType(), ttype<nInt>::get());
    ASSERT_TRUE(nul(*p1.getOrigin()));
}*/
