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

TEST_F(visitorTest, visitComplexExpressions) {
    make().parse(R"SRC(
        def obj
            foo() flt
                5.0

        main() flt
            o := obj()
            sys.con.print(o.foo() as str)
            return o.foo() as flt
    )SRC").shouldVerified(true);

    node& root = getSubPack();
    ASSERT_FALSE(nul(root));

    struct myVisitor : public visitor {
        myVisitor(): metO(0), metAsFlt(0), metFlt5(false) {}

        using visitor::onVisit;
        void onVisit(const std::string& name, getExpr& got) override {
            NAMU_DI("subname=%s", got.getSubName().c_str());
            if(got.getSubName() == "o")
                metO++;
        }

        void onVisit(const std::string& name, asExpr& as) override {
            if(as.getAs().as<node>()->isSub<nFlt>())
                metAsFlt++;
        }

        void onVisit(const std::string& name, nFlt& f) override {
            if(f.get() == 5.0f)
                metFlt5 = true;
        }

        nint metO;
        nint metAsFlt;
        nbool metFlt5;
    };

    myVisitor v;
    v.start(root);
    ASSERT_EQ(v.metO, 2);
    ASSERT_EQ(v.metAsFlt, 1);
    ASSERT_TRUE(v.metFlt5);
}

TEST_F(visitorTest, visitComplexExpressions2) {
    make().parse(R"SRC(
        def obj
            foo(a int) flt
                return 5.0 + a

        main() flt
            o := obj()
            ret := o.foo() as flt
            ret = ret * 2
            return ret
    )SRC").shouldVerified(true);

    node& root = getSubPack();
    ASSERT_FALSE(nul(root));

    struct myVisitor : public visitor {
        myVisitor(): metInt2(false), metRet(false) {}

        using visitor::onVisit;
        void onVisit(const std::string& name, FAOExpr& fao) override {
            tstr<nInt> num2 = ((node&) fao.getRight()).as<nInt>();
            if(num2->cast<nint>() == 2)
                metInt2 = true;
        }

        void onVisit(const std::string& name, assignExpr& a) override {
            getExpr& leftGet = ((node&) a.getLeft()).cast<getExpr>();
            if(nul(leftGet)) return;

            if(leftGet.getSubName() != "ret") return;
            metRet = true;
        }

        nbool metInt2;
        nbool metRet;
    };

    myVisitor v;
    v.start(root);
    ASSERT_TRUE(v.metInt2);
    ASSERT_TRUE(v.metRet);
}
