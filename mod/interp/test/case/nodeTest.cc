#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class myFunc : public mgdFunc {
        WRD_CLASS(myFunc, mgdFunc)

    public:
        myFunc(): super("myFunc") {}

        void setUp() {
            _executed = false;
        }

        str run(const ncontainer& args) override {
            WRD_I("hello world!");
            _executed = true;
            return str();
        }

        wbool isRun() const {
            return _executed;
        }

        const wtype& getReturnType() const override {
            return ttype<node>::get();
        }

        const wtypes& getTypes() const override {
            static wtypes inner;
            if(inner.size() == 0)
                inner.push_back(&ttype<obj>::get());

            return inner;
        }

    protected:
        str _onRun(narr& args) override {
            return str();
        }

    private:
        wbool _executed;
    };
}

namespace {
    struct myObj : public mgdObj {
        WRD_CLASS(myObj, mgdObj)

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
}

TEST(nodeTest, testManuallyMakeNodeStructure) {
    // prepare:
    tstr<nchain> frameEmulator;
    myObj obj;
    myFunc func;
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);

    obj.subs().add(func);
    myFunc funcOffunc;
    func.subs().add(funcOffunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // when:
    frameEmulator.bind(obj.subs());
    //  push another:
    nchain* chnOffunc = nchain::wrap(func.subs());
    chnOffunc->link(*frameEmulator);
    frameEmulator.bind(*chnOffunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // then:
    ASSERT_EQ(chnOffunc->len(), 2);
    ASSERT_EQ(chnOffunc->len(), 2);
    ASSERT_EQ(chnOffunc->len(), 2);

    int n=0;
    for(const auto& elem : *chnOffunc)
        WRD_E("[%d]=%s", n++, elem.getType().getName().c_str());

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    ASSERT_EQ(n, 2);
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);
}

TEST(nodeTest, testManualNativefuncCall) {
    // prepare:
    myFunc func;

    myObj obj;
    obj.subs().add(func);

    narr args;
    args.add(obj);
    narr subs = obj.subAll(func.getName(), args);
    ASSERT_EQ(subs.len(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
}

TEST(nodeTest, testImmutablePositive) {
    tref<wFlt> r1(new wFlt(1.0f));
    wrd::ref r2 = r1;
    ASSERT_TRUE(r1);
    ASSERT_TRUE(r2);
    ASSERT_EQ(*r1, *r2);

    r1->get() = 0.5f;
    ASSERT_NE(*r1, *r2);
}

TEST(nodeTest, testImmutableNegative) {
    wrd::ref r1(new myObj(1));
    wrd::ref r2 = r1;
    ASSERT_TRUE(r1);
    ASSERT_TRUE(r2);
    ASSERT_EQ(*r1, *r2);

    r1->cast<myObj>().val = 2;
    ASSERT_EQ(*r1, *r2);
}
