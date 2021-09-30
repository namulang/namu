#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class originObj : public obj {
        WRD(CLASS(originObj, obj))

    public:
        originObj(): super("", *new nchain()) {}
        originObj(const std::string& name, const nchain& subs): super(name, subs) {}
        originObj(const me& rhs) {
            _subs = rhs._subs;
        }

        const obj& getOrigin() const override {
            return *this;
        }

        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }

        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            _subs = rhs._subs;
            return *this;
        }
    };
}

TEST(objTest, testMakeOriginObj) {
    const wchar* o2Name = "o2";
    originObj o1, o2(o2Name, *new nchain());
    ASSERT_STREQ(o1.getName().c_str(), "");
    ASSERT_STREQ(o2.getName().c_str(), o2Name);
    ASSERT_NE(o1.getId(), o2.getId());
    ASSERT_FALSE(nul(o1.subs()));
    ASSERT_FALSE(nul(o2.subs()));

    nchain* newSubs = new nchain();
    originObj o3("", *newSubs);
    ASSERT_FALSE(nul(o3.subs()));

    ASSERT_EQ(o3.subs().len(), 0);
    newSubs->add(o1);
    newSubs->add(o2);
    ASSERT_EQ(o3.subs().len(), 2);

    ASSERT_TRUE(nul(o3["o1"]));
    node& found = o3[o2Name];
    ASSERT_FALSE(nul(found));
    ASSERT_EQ(&found, &o2);
}

TEST(objTest, testCloneOriginObj) {
    const wchar* o2Name = "wow";
    originObj o1, o2(o2Name, *new nchain());
    nchain* newSubs = new nchain();
    originObj o3("", *newSubs);

    tstr<originObj> clone(o3.clone());
    ASSERT_FALSE(nul(*clone));

    ASSERT_EQ(clone->subs().len(), 0);
    ASSERT_EQ(o3.subs().len(), 0);
    newSubs->add(o1);
    newSubs->add(o2);
    ASSERT_EQ(o3.subs().len(), 2);
    ASSERT_EQ(clone->subs().len(), 2);

    ASSERT_TRUE(nul(clone->sub("o1")));
    node& found = clone->sub(o2Name);
    ASSERT_FALSE(nul(found));
    ASSERT_EQ(&found, &o2);
}
