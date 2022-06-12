#include "../../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class myObj : public obj {
        WRD(CLASS(myObj, obj))

    public:
        const obj& getOrigin() const override { return *this; }

        using super::subs;
        nbicontainer& subs() override { return *_subs; }

    private:
        tstr<scopes> _subs;
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

    ASSERT_FALSE(intType.isImpli<wStr>());
    ASSERT_FALSE(intObj.isImpli<wStr>());
    ASSERT_TRUE(intType.isImpli<wFlt>());
    ASSERT_TRUE(intObj.isImpli<wFlt>());
    ASSERT_FALSE(inttType.isImpli<myObj>());
    ASSERT_FALSE(myO.isImpli<wInt>());

    ASSERT_TRUE(intType.is<wBool>());
    ASSERT_TRUE(intObj.is<wBool>());
    ASSERT_FALSE(inttType.is<myObj>());
    ASSERT_FALSE(myO.getType().is<wInt>());
}

TEST(wtypeTest, makeTest) {
    tstr<wInt> new1 = ttype<wInt>().makeAs<wInt>();
    ASSERT_TRUE(new1);
    ASSERT_EQ(new1->get(), 0);
}
