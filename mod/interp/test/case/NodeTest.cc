#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

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

    wbool isRun() const {
        return _executed;
    }

private:
    wbool _executed;
};

TEST(NodeTest, testManualNativeFuncCall) {
    // prepare:
    MyFunc func;

    Obj obj;
    obj.subs().add(func);

    NArr args;
    NArr subs = obj.sub(func.getName(), args);
    ASSERT_EQ(subs.getLen(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
}
