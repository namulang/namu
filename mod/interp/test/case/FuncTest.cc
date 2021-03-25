#include "../common/dep.hpp"
#include <functional>

using namespace wrd;
using namespace std;

class MyFunc : public Func {
    WRD_CLASS(MyFunc, Func)

public:
    MyFunc(): Super("MyFunc") {}

    void setUp() {
        _executed = false;
        _res = false;
    }

    wbool isRun() const {
        return _executed;
    }

    void setLambda(function<wbool(const StackFrame&)> lambda) {
        _lambda = lambda;
    }

    wbool isSuccess() const {
        return _res;
    }

protected:
    Str _onRun(NContainer& args) override {
        WRD_I("hello world!");
        _executed = true;

        if(_lambda)
            _res = _lambda((StackFrame&) Thread::get().getStackFrame());
        return Str();
    }

private:
    wbool _executed;
    wbool _res;
    function<wbool(const StackFrame&)> _lambda;
};

struct FuncFixture : public ::testing::Test {
    void SetUp() {
        func.setUp();
        ASSERT_FALSE(func.isRun());
    }

    MyFunc func;
};

TEST_F(FuncFixture, testFuncConstructNewFrame) {
    Obj obj;
    obj.subs().add(func);
    WRD_E("obj.len=%d", obj.subs().getLen());
    int n = 0;
    for(Iter e=obj.subs().head(); e ;e++) {
        WRD_E(" - fr[%d]=%s", n++, e->getType().getName().c_str());
    }

    NArr args;
    args.add(obj);

    func.setLambda([this, &obj](const StackFrame& sf) {
        if(sf.getLen() != 1) return false;

        const Frame& fr = sf[0];
        if(nul(fr)) return false;

        const NChain& funcScope = fr.subs().cast<NChain>();
        if(nul(funcScope)) return WRD_E("nul(funcScope)"), false;
        const NChain& objScope = funcScope.getNext();
        if(nul(objScope)) return WRD_E("nul(objScope)"), false;
        if(&obj.subs() != &objScope) return false;

        int n = 0;
        WRD_E("fr.len=%d", fr.subs().getLen());
        for(Iter e=fr.subs().head(); e ;e++) {
            WRD_E(" - fr[%d]=%s", n++, e->getType().getName().c_str());
        }

        NArr foundFunc = fr.sub(func.getName());
        if(foundFunc.getLen() != 1) return false;

        return true;
    });
    func.run(args);
    ASSERT_TRUE(func.isRun());
    ASSERT_TRUE(func.isSuccess());
    ASSERT_TRUE(func.isSuccess());
}
