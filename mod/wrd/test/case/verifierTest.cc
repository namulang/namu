#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

struct verifierTest : public ::testing::Test {
	void SetUp();
	void TearDown();

	verifications& getVerifications(const type& typ) {
		return veri._getVerifications(typ);
	}

	verifier veri;
};

namespace {
	static constexpr wint TEST_VERI_CODE_WITH = 99999990; // not to be duplicated.

    struct myObj : public mgdObj {
        WRD(CLASS(myObj, mgdObj))

    public:
        myObj(int newVal = 0): val(newVal) {}

        int val;

        wbool _onSame(const typeProvidable& rhs) const override {
            const myObj& cast = (const myObj&) rhs;
            return val == cast.val;
        }

        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }
    };

	WRD_VERIFY(myObj, {
		if(it.val == 0)
			return _err<err>(TEST_VERI_CODE_WITH + 1, "val is 0");
		return false;
	})
}

void verifierTest::SetUp() {
}
void verifierTest::TearDown() {
}

TEST_F(verifierTest, verificationLoaded) {
	verifications& veris = getVerifications(ttype<myObj>::get());
	wcnt len = veris.size();
	ASSERT_TRUE(len > 0);
}

TEST_F(verifierTest, verifyMyObj) {
	myObj obj;
	verifier veri;
	errReport report;
	veri.verify(obj, report);

	ASSERT_TRUE(report); // should have an err.
	ASSERT_EQ(report.len(), 1);

	const err& e = report[0];
	ASSERT_FALSE(nul(e));
	ASSERT_EQ(e.fType, err::ERR);
	ASSERT_EQ(e.code, TEST_VERI_CODE_WITH + 1);
	ASSERT_EQ(e.msg, "val is 0");
	report.rel();

	obj.val = 1;
	veri.verify(obj, report);
	ASSERT_FALSE(report);
}

TEST_F(verifierTest, verifyNestedNode) {

}
