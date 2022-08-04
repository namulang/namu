#include "../../common/dep.hpp"

using namespace namu;
using namespace std;

namespace {
    struct myObj : public obj {
        NAMU(CLASS(myObj, obj))

    public:
        myObj(int newVal = 0): val(newVal) {}

        int val;

        nbool _onSame(const typeProvidable& rhs) const override {
            const myObj& cast = (const myObj&) rhs;
            return val == cast.val;
        }
    };

    NAMU_VERIFY(myObj, {
        if(it.val == 0)
            _err(errCode::ERR_CODE_END);
    })

    struct mymyObj : public myObj {
        NAMU(CLASS(mymyObj, myObj))

    public:
        mymyObj(): grade(0.0f) {}

        nflt grade;
    };

    NAMU_VERIFY(mymyObj, {
        if(it.grade <= 0.0f)
            _warn(point {1, 1}, errCode::ERR_CODE_START);
    })
}

struct verifierTest : public ::testing::Test {
    void SetUp() {}
    void TearDown() {}

    verifications& getVerifications(const type& typ) {
        return veri._getVerifications(typ);
    }

    verifier veri;
};


TEST_F(verifierTest, verificationLoaded) {
    verifications& veris = getVerifications(ttype<myObj>::get());
    ncnt len = veris.size();
    ASSERT_TRUE(len > 0);
}

TEST_F(verifierTest, verifyMyObj) {
    myObj obj;
    verifier veri;
    errReport report;
    veri.setReport(report).verify(obj);

    ASSERT_TRUE(report); // should have an err.
    ASSERT_EQ(report.len(), 1);

    const err& e = report[0];
    ASSERT_FALSE(nul(e));
    ASSERT_EQ(e.fType, err::ERR);
    ASSERT_EQ(e.code, errCode::ERR_CODE_END);
    ASSERT_EQ(e.msg, err::getErrMsg(e.code));

    report.log();
    report.rel();

    obj.val = 1;
    veri.verify(obj);
    ASSERT_FALSE(report);
}

TEST_F(verifierTest, errMsgFor0ShouldExist) {
    ASSERT_TRUE(errCode::ERR_CODE_END > 0);
    ASSERT_EQ(err::getErrMsg(UNKNOWN), "unknown");
}

TEST_F(verifierTest, verifyInheritedClass) {
    mymyObj it;
    it.val = 0;
    it.grade = -0.1f;

    errReport report;
    verifier veri;
    veri.setReport(report).verify(it);

    ASSERT_TRUE(report);
    ASSERT_EQ(report.len(), 2);

    const err& myObjE = report[0]; // verification of myObj
    ASSERT_FALSE(nul(myObjE));
    ASSERT_EQ(myObjE.fType, err::ERR);
    ASSERT_EQ(myObjE.code, errCode::ERR_CODE_END);
    ASSERT_EQ(myObjE.msg, err::getErrMsg(myObjE.code));

    const err& mymyObjE = report[1]; // of mymyObj
    ASSERT_FALSE(nul(mymyObjE));
    ASSERT_EQ(mymyObjE.fType, err::WARN);
    ASSERT_EQ(mymyObjE.code, errCode::ERR_CODE_START);
    ASSERT_EQ(mymyObjE.msg, err::getErrMsg(mymyObjE.code));

    const srcErr& cast = mymyObjE.cast<srcErr>();
    ASSERT_FALSE(nul(cast));
    ASSERT_EQ(cast.pos.row, 1);
    ASSERT_EQ(cast.pos.col, 1);
}

TEST_F(verifierTest, verifyNestedObject) {
    myObj o1;
    o1.val = 1;

    mymyObj o2;
    o2.val = 1;
    o2.grade = 0.0f; // err
    o1.subs().add("o2", o2);
    ASSERT_EQ(o1.subs().len(), 1);
    mymyObj& o2Candidate = o1.sub<mymyObj>([](const std::string& name, const auto& elem) { return true; });
    ASSERT_FALSE(nul(o2Candidate));
    ASSERT_EQ(&o2, &o2Candidate);

    errReport report;
    verifier veri;
    veri.setReport(report).verify(o1);
    ASSERT_FALSE(report);
    ASSERT_FALSE(report.hasErr());
    ASSERT_TRUE(report.hasWarn());
    ASSERT_EQ(report.len(), 1);

    const srcErr& e = report[0].cast<srcErr>();
    ASSERT_FALSE(nul(e));
    ASSERT_EQ(e.fType, err::WARN);
    ASSERT_EQ(e.code, errCode::ERR_CODE_START);
    ASSERT_EQ(e.msg, err::getErrMsg(e.code));
    ASSERT_EQ(e.pos.row, 1);
    ASSERT_EQ(e.pos.col, 1);
}

TEST_F(verifierTest, verifySubedObject) {
    mymyObj o1;
    o1.val = 1;
    o1.grade = 2.5f;

    myObj o2; // o2.val = 0 so it will occur an error.
    o1.subs().add("o2", o2);

    errReport rpt;
    verifier v;
    // by verification of node class, this makes verifier iterate all subs nodes including o2.
    v.setReport(rpt).verify(o1);
    ASSERT_TRUE(rpt); // should contain some error.

    ASSERT_EQ(rpt.len(), 1);

    const err& e = rpt[0];
    ASSERT_EQ(e.fType, err::ERR);
    ASSERT_EQ(e.code, errCode::ERR_CODE_END);
}
