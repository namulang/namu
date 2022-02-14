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
	wrd::ref r(org);
	ASSERT_TRUE(r);
	ASSERT_EQ(&r.get(), &r->cast<obj>().getOrigin());
	ASSERT_EQ(&r.get(), org);

	wInt* i = new wInt(1);
    wrd::ref r2(i);
	ASSERT_TRUE(r2);
	ASSERT_EQ(r2.get<wInt>().get(), 1);
	ASSERT_EQ(&r2.get(), i);

	wrd::ref r3(r2);
	ASSERT_TRUE(r3);
	ASSERT_EQ(r3.get<wInt>().get(), 1);
	ASSERT_NE(&r3->cast<wInt>(), i);
}
