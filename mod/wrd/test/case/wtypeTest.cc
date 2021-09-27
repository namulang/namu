#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class myObj : public obj {
        WRD(CLASS(myObj, obj))

    public:
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }

        const obj& getOrigin() const override { return *this; }
    };
}

TEST(wtypeTest, basicWTypeAPITest) {
    wInt intObj;
    myObj myO;
    const wtype& myType = myO.getType();
    const wtype& intType = intObj.getType();
    const wtype& inttType = ttype<wInt>::get();

    ASSERT_EQ(&intType, &inttType);
    ASSERT_EQ(intType, inttType);

    ASSERT_FALSE(myType.isImmutable());
    ASSERT_TRUE(intType.isImmutable());

    ASSERT_TRUE(intType.isImpli<wStr>());
    ASSERT_TRUE(intObj.isImpli<wStr>());
    ASSERT_FALSE(inttType.isImpli<myObj>());
    ASSERT_FALSE(myO.isImpli<wInt>());

    ASSERT_TRUE(intType.is<wStr>());
    ASSERT_TRUE(intObj.is<wStr>());
    ASSERT_FALSE(inttType.is<myObj>());
    ASSERT_FALSE(myO.getType().is<wInt>());
}

