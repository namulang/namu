#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct myObj : public obj {
        WRD_CLASS(myObj, obj)

    public:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }
    };
}

TEST(trefTest, testCast) {
    tref<myObj> obj1(new myObj());

    myObj& cast = *obj1;
    ASSERT_FALSE(nul(cast));
}
