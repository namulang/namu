#include "../../namuTest.hpp"

using namespace namu;
using namespace std;

struct objTest : public namuTest {};

namespace {
    class originObj : public obj {
        NAMU(CLASS(originObj, obj))

    public:
        originObj(): super(new mgdType("originObj")), _subs(*new scopes()) {}
        originObj(const scopes& subs): super(new mgdType("originObj")), _subs(subs) {}
        originObj(const me& rhs) {
            _subs = rhs._subs;
        }

        const obj& getOrigin() const override {
            return *this;
        }

        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            _subs = rhs._subs;
            return *this;
        }

        using super::subs;
        nbicontainer& subs() override { return *_subs; }

    private:
        tstr<scopes> _subs;
    };
}

TEST_F(objTest, testMakeOriginObj) {
    const nchar* o2Name = "o2";
    originObj o1, o2(*new scopes());
    ASSERT_NE(o1.getId(), o2.getId());
    ASSERT_FALSE(nul(o1.subs()));
    ASSERT_FALSE(nul(o2.subs()));

    scopes* newSubs = new scopes();
    originObj o3(*newSubs);
    ASSERT_FALSE(nul(o3.subs()));

    ASSERT_EQ(o3.subs().len(), 0);
    newSubs->add("o1", o1);
    newSubs->add(o2Name, o2);
    ASSERT_EQ(o3.subs().len(), 2);

    ASSERT_TRUE(nul(o3[""]));
    ASSERT_FALSE(nul(o3["o1"]));
    node& found = o3[o2Name];
    ASSERT_FALSE(nul(found));
    ASSERT_EQ(&found, &o2);
}

TEST_F(objTest, testCloneOriginObj) {
    const nchar* o2Name = "wow";
    originObj o1, o2(*new scopes());
    scopes* newSubs = new scopes();
    originObj o3(*newSubs);

    tstr<originObj> clone((originObj*) o3.clone());
    ASSERT_FALSE(nul(*clone));

    ASSERT_EQ(clone->subs().len(), 0);
    ASSERT_EQ(o3.subs().len(), 0);
    newSubs->add("o1", o1);
    newSubs->add(o2Name, o2);
    ASSERT_EQ(o3.subs().len(), 2);
    ASSERT_EQ(clone->subs().len(), 2);

    ASSERT_TRUE(nul(clone->sub("o3")));
    node& found = clone->sub(o2Name);
    ASSERT_FALSE(nul(found));
    ASSERT_EQ(&found, &o2);
}

TEST_F(objTest, cloneByRunFunc) {
    nInt a(5);
    nInt& a1 = (nInt&) *a.clone();
    ASSERT_NE(&a, &a1);
    ASSERT_EQ(a.cast<int>(), a1.cast<int>());
}

TEST_F(objTest, addElementIntoOwns) {
    obj my(new mgdType("my"));
    ASSERT_EQ(my.subs().len(), 0);

    my.subs().add("banana", new nInt(1));
    ASSERT_EQ(my.getShares().len(), 0);
    ASSERT_EQ(my.getOwns().len(), 1);
    ASSERT_EQ(my.getOwns()["banana"].cast<int>(), 1);
}

TEST_F(objTest, objType) {
    originObj o1;
    const type& t = o1.getType();
    ASSERT_FALSE(nul(t));
    ASSERT_EQ(t.getName(), "originObj");
    ASSERT_TRUE(t.getSuper() == ttype<obj>());
}
