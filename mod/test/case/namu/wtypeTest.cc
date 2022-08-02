#include "../../common/dep.hpp"

using namespace namu;
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

TEST(wtypeTest, allImplicitCastingForPrimitives) {
    wInt i;
    wFlt f;
    wBool b;
    wChar c;
    wStr s;

    // int:
    ASSERT_TRUE(i.isImpli<wInt>());
    ASSERT_TRUE(i.isImpli<wFlt>());
    ASSERT_TRUE(i.isImpli<wBool>());
    ASSERT_TRUE(i.isImpli<wChar>());
    ASSERT_FALSE(i.isImpli<wStr>());

    // float:
    ASSERT_TRUE(f.isImpli<wInt>());
    ASSERT_TRUE(f.isImpli<wFlt>());
    ASSERT_TRUE(f.isImpli<wBool>());
    ASSERT_TRUE(f.isImpli<wChar>());
    ASSERT_FALSE(f.isImpli<wStr>());

    // bool:
    ASSERT_FALSE(b.isImpli<wInt>());
    ASSERT_FALSE(b.isImpli<wFlt>());
    ASSERT_TRUE(b.isImpli<wBool>());
    ASSERT_FALSE(b.isImpli<wChar>());
    ASSERT_FALSE(b.isImpli<wStr>());

    // char:
    ASSERT_FALSE(c.isImpli<wInt>());
    ASSERT_FALSE(c.isImpli<wFlt>());
    ASSERT_TRUE(c.isImpli<wBool>());
    ASSERT_TRUE(c.isImpli<wChar>());
    ASSERT_FALSE(c.isImpli<wStr>());

    // str:
    ASSERT_FALSE(s.isImpli<wInt>());
    ASSERT_FALSE(s.isImpli<wFlt>());
    ASSERT_FALSE(s.isImpli<wBool>());
    ASSERT_FALSE(s.isImpli<wChar>());
    ASSERT_TRUE(s.isImpli<wStr>());
}
