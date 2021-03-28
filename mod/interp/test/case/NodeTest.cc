#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    class MyFunc : public Func {
        WRD_CLASS(MyFunc, Func)

    public:
        MyFunc(): Super("MyFunc") {}

        void setUp() {
            _executed = false;
        }

        Str run(NContainer& args) override {
            WRD_I("hello world!");
            _executed = true;
            return Str();
        }

        using Super::subs;
        NContainer& subs() override { return _shares; }

        wbool isRun() const {
            return _executed;
        }

    protected:
        Str _onRun(NContainer& args) override {
            return Str();
        }

    private:
        wbool _executed;
        NArr _shares;
    };
}

TEST(NodeTest, testManuallyMakeNodeStructure) {
    // prepare:
    TStr<NChain> frameEmulator;
    Obj obj;
    MyFunc func;
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);

    obj.subs().add(func);
    MyFunc funcOfFunc;
    func.subs().add(funcOfFunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOfFunc.tag.chkId=%d", funcOfFunc.getBindTag().getId().chkN);

    // when:
    frameEmulator.bind(obj.subs());
    //  push another:
    NChain* chnOfFunc = new NChain(func.subs());
    chnOfFunc->link(*frameEmulator);
    frameEmulator.bind(*chnOfFunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOfFunc.tag.chkId=%d", funcOfFunc.getBindTag().getId().chkN);

    // then:
    ASSERT_EQ(chnOfFunc->getLen(), 2);
    ASSERT_EQ(chnOfFunc->getLen(), 2);
    ASSERT_EQ(chnOfFunc->getLen(), 2);

    int n=0;
    for(Iter e=chnOfFunc->head(); e ;e++)
        WRD_E("[%d]=%s", n++, e->getType().getName().c_str());

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOfFunc.tag.chkId=%d", funcOfFunc.getBindTag().getId().chkN);

    ASSERT_EQ(n, 2);
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOfFunc.tag.chkId=%d", funcOfFunc.getBindTag().getId().chkN);
}

TEST(NodeTest, testManualNativeFuncCall) {
    // prepare:
    MyFunc func;

    Obj obj;
    obj.subs().add(func);

    NArr args;
    args.add(obj);
    NArr subs = obj.sub(func.getName(), args);
    ASSERT_EQ(subs.getLen(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
}
