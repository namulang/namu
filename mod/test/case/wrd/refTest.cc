#include "../../common/dep.hpp"

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

TEST(refTest, testImmutableAndClonable) {
	obj* org = new myObj();
	wrd::ref r(org, "");
	ASSERT_TRUE(r);
	ASSERT_EQ(&r.get(), &r->cast<obj>().getOrigin());
	ASSERT_EQ(&r.get(), org);

	wInt* i = new wInt(1);
    wrd::ref r2(i, "");
	ASSERT_TRUE(r2);
	ASSERT_EQ(r2.get<wInt>().get(), 1);
	ASSERT_EQ(&r2.get(), i);

	wrd::ref r3(r2);
	ASSERT_TRUE(r3);
	ASSERT_EQ(r3.get<wInt>().get(), 1);
	ASSERT_NE(&r3->cast<wInt>(), i);
}

TEST(refTest, refCast) {
    wInt int1(1);
    wrd::ref r(int1, "");

    ASSERT_EQ(int1.get(), r->cast<wInt>().get());
    ASSERT_EQ(r.cast<wInt>().get(), r->cast<wInt>().get());
    ASSERT_EQ(r->getType(), int1.getType());
    ASSERT_EQ(r.getType(), r->getType());
    ASSERT_EQ(r.cast<int>(), int1.cast<int>());
    ASSERT_EQ(r.cast<int>(), 1);
}

TEST(refTest, refCastRefShouldReturnThis) {
    wInt int1(1);
    wrd::ref r(int1, ""), r2(r);

    ASSERT_EQ(r.cast<wInt>().get(), 1);
    ASSERT_EQ(r2.cast<wInt>().get(), 1); // r2->r->int1.get()
    ASSERT_EQ(&r2.cast<wrd::ref>(), &r2); // if cast<ref> to a ref then it returns 'this'.
    ASSERT_EQ(r.cast<int>(), 1);
    ASSERT_EQ(r2.cast<int>(), 1); // r2->r->cast<int>()
}

TEST(refTest, refNameIsUniqueAttribute) {
    wInt int1(1);
    wrd::ref r1(int1, ""), r2(&int1, "r2"), r3(r2);

    ASSERT_EQ(r1.getName(), "");
    ASSERT_EQ(r2.getName(), "r2");
    ASSERT_EQ(r1.cast<int>(), r2.cast<int>());
    ASSERT_EQ(r3.getName(), r2.getName());
    ASSERT_EQ(r2.cast<int>(), r3.cast<int>());

    std::string name = "newName";
    r3.setName(name);
    ASSERT_EQ(r3.getName(), name);
}
