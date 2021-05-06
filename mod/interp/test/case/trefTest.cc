#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct myObj : public mgdObj {
        WRD_CLASS(myObj, mgdObj)

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
