#include "../../common/dep.hpp"

using namespace namu;
using namespace std;

namespace {
    class myObj : public obj {
        NAMU(CLASS(myObj, obj))

    public:
        const obj& getOrigin() const override { return *this; }

        using super::subs;
        nbicontainer& subs() override { return *_subs; }

    private:
        tstr<scopes> _subs;
    };
}

TEST(ntypeTest, basicWTypeAPITest) {
    nInt intObj;
    myObj myO;
    const ntype& myType = myO.getType();
    const ntype& intType = intObj.getType();
    const ntype& inttType = ttype<nInt>::get();

    ASSERT_EQ(&intType, &inttType);
    ASSERT_EQ(intType, inttType);

    ASSERT_FALSE(myType.isImmutable());
    ASSERT_TRUE(intType.isImmutable());

    ASSERT_FALSE(intType.isImpli<nStr>());
    ASSERT_FALSE(intObj.isImpli<nStr>());
    ASSERT_TRUE(intType.isImpli<nFlt>());
    ASSERT_TRUE(intObj.isImpli<nFlt>());
    ASSERT_FALSE(inttType.isImpli<myObj>());
    ASSERT_FALSE(myO.isImpli<nInt>());

    ASSERT_TRUE(intType.is<nBool>());
    ASSERT_TRUE(intObj.is<nBool>());
    ASSERT_FALSE(inttType.is<myObj>());
    ASSERT_FALSE(myO.getType().is<nInt>());
}

TEST(ntypeTest, makeTest) {
    tstr<nInt> new1 = ttype<nInt>().makeAs<nInt>();
    ASSERT_TRUE(new1);
    ASSERT_EQ(new1->get(), 0);
}

TEST(ntypeTest, allImplicitCastingForPrimitives) {
    nInt i;
    nFlt f;
    nBool b;
    nChar c;
    nStr s;

    // int:
    ASSERT_TRUE(i.isImpli<nInt>());
    ASSERT_TRUE(i.isImpli<nFlt>());
    ASSERT_TRUE(i.isImpli<nBool>());
    ASSERT_TRUE(i.isImpli<nChar>());
    ASSERT_FALSE(i.isImpli<nStr>());

    // float:
    ASSERT_TRUE(f.isImpli<nInt>());
    ASSERT_TRUE(f.isImpli<nFlt>());
    ASSERT_TRUE(f.isImpli<nBool>());
    ASSERT_TRUE(f.isImpli<nChar>());
    ASSERT_FALSE(f.isImpli<nStr>());

    // bool:
    ASSERT_TRUE(b.isImpli<nInt>());
    ASSERT_TRUE(b.isImpli<nFlt>());
    ASSERT_TRUE(b.isImpli<nBool>());
    ASSERT_TRUE(b.isImpli<nChar>());
    ASSERT_FALSE(b.isImpli<nStr>());

    // char:
    ASSERT_FALSE(c.isImpli<nInt>());
    ASSERT_FALSE(c.isImpli<nFlt>());
    ASSERT_TRUE(c.isImpli<nBool>());
    ASSERT_TRUE(c.isImpli<nChar>());
    ASSERT_FALSE(c.isImpli<nStr>());

    // str:
    ASSERT_FALSE(s.isImpli<nInt>());
    ASSERT_FALSE(s.isImpli<nFlt>());
    ASSERT_FALSE(s.isImpli<nBool>());
    ASSERT_FALSE(s.isImpli<nChar>());
    ASSERT_TRUE(s.isImpli<nStr>());
}
