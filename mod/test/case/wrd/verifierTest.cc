#include "../../common/dep.hpp"

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
			return _err<err>(err::BASE_TEST_CODE + 1);
		return false;
	})

	struct mymyObj : public myObj {
		WRD(CLASS(mymyObj, myObj))

	public:
		mymyObj(): grade(0.0f) {}

		wflt grade;
	};

	WRD_VERIFY(mymyObj, {
		if(it.grade <= 0.0f)
			return _warn<srcErr>(err::BASE_TEST_CODE + 2, area {{1, 1}, {1, 5}});
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
	ASSERT_EQ(e.code, err::BASE_TEST_CODE + 1);
	ASSERT_EQ(e.msg, "val is 0");

	report.log();
	report.rel();

	obj.val = 1;
	veri.verify(obj, report);
	ASSERT_FALSE(report);
}

TEST_F(verifierTest, errMsgFor0ShouldExist) {
	const msgMap& msgs = err::getErrMsgs();
	ASSERT_TRUE(msgs.size() > 0);
	ASSERT_EQ(msgs.at(0), "unknown");
}

TEST_F(verifierTest, verifyInheritedClass) {
	mymyObj it;
	it.val = 0;
	it.grade = -0.1f;

	errReport report;
	verifier veri;
	veri.verify(it, report);

	ASSERT_TRUE(report);
	ASSERT_EQ(report.len(), 2);

	const err& myObjE = report[0]; // verification of myObj
	ASSERT_FALSE(nul(myObjE));
	ASSERT_EQ(myObjE.fType, err::ERR);
	ASSERT_EQ(myObjE.code, err::BASE_TEST_CODE + 1);
	ASSERT_EQ(myObjE.msg, "val is 0");

	const err& mymyObjE = report[1]; // of mymyObj
	ASSERT_FALSE(nul(mymyObjE));
	ASSERT_EQ(mymyObjE.fType, err::WARN);
	ASSERT_EQ(mymyObjE.code, err::BASE_TEST_CODE + 2);
    ASSERT_EQ(mymyObjE.msg.substr(0, 5), "grade");

	const srcErr& cast = mymyObjE.cast<srcErr>();
	ASSERT_FALSE(nul(cast));
	ASSERT_EQ(cast.srcArea.start.row, 1);
	ASSERT_EQ(cast.srcArea.start.col, 1);
	ASSERT_EQ(cast.srcArea.end.row, 1);
	ASSERT_EQ(cast.srcArea.end.col, 5);
}

TEST_F(verifierTest, verifyNestedObject) {
	myObj o1;
	o1.val = 1;

	mymyObj o2;
	o2.val = 1;
	o2.grade = 0.0f; // err
	o1.subs().add(o2);
	ASSERT_EQ(o1.subs().len(), 1);
	mymyObj& o2Candidate = o1.sub<mymyObj>([](const auto& elem) { return true; });
	ASSERT_FALSE(nul(o2Candidate));
	ASSERT_EQ(&o2, &o2Candidate);

	errReport report;
	verifier veri;
	veri.verify(o1, report);
	ASSERT_FALSE(report);
	ASSERT_FALSE(report.hasErr());
	ASSERT_TRUE(report.hasWarn());
	ASSERT_EQ(report.len(), 1);

	const srcErr& e = report[0].cast<srcErr>();
	ASSERT_FALSE(nul(e));
	ASSERT_EQ(e.fType, err::WARN);
	ASSERT_EQ(e.code, err::BASE_TEST_CODE + 2);
	ASSERT_EQ(e.msg.substr(0, 5), "grade");
	ASSERT_EQ(e.srcArea.start.row, 1);
	ASSERT_EQ(e.srcArea.start.col, 1);
	ASSERT_EQ(e.srcArea.end.row, 1);
	ASSERT_EQ(e.srcArea.end.col, 5);
}
