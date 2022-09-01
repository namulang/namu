#include "../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

struct visitorTest : public namuSyntaxTest {};

TEST_F(visitorTest, iterateManuallyConstructedNodes) {
    obj o;
    o.subs().add("foo1", new mgdFunc(params(), *new nInt()));
    o.subs().add("val1", new nInt());

    obj o2;
    o2.subs().add("foo2", new mgdFunc(params(), *new nFlt()));
    o2.subs().add("val2", new nFlt());
    o2.subs().add("o", o);

    struct myVisitor : public visitor {
        nbool metFoo1;
        nbool metVal1;
        nbool metFoo2;
        nbool metVal2;

        myVisitor(): metFoo1(false), metVal1(false), metFoo2(false), metVal2(false) {}

        void onVisit(const std::string& name, mgdFunc& fun) override {
            if(name == "foo1")
                metFoo1 = true;
            if(name == "foo2") {
                metFoo2 = true;
                EXPECT_TRUE(fun.getRet().isSub<nFlt>());
            }
        }
        void onVisit(const std::string& name, nInt& o) override {
            if(name == "val1")
                metVal1 = true;
        }
        void onVisit(const std::string& name, nFlt& o) override {
            if(name == "val2")
                metVal2 = true;
        }
    };
    myVisitor v;
    ASSERT_FALSE(v.metFoo1);
    ASSERT_FALSE(v.metFoo2);
    ASSERT_FALSE(v.metVal1);
    ASSERT_FALSE(v.metVal2);

    v.start(o2);

    ASSERT_TRUE(v.metFoo1);
    ASSERT_TRUE(v.metFoo2);
    ASSERT_TRUE(v.metVal1);
    ASSERT_TRUE(v.metVal2);
}
