#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct packTest : public syntaxTest {};

    class myfunc : public mgdFunc {
        WRD(CLASS(myfunc, mgdFunc))

        class myBlock : public blockExpr {
            WRD(CLASS(myBlock, blockExpr))

        public:
            str run(const containable& args) override {
                WRD_I("hello world!");
                _executed = true;

                if(_lambda)
                    _res = _lambda(args, (stackFrame&) wrd::thread::get().getStackFrame());
                return str();
            }

            void setLambda(function<wbool(const containable&, const stackFrame&)> lambda) {
                _lambda = lambda;
            }

            function<wbool(const containable&, const stackFrame&)> _lambda;
            wbool _res;
            wbool _executed;
        };

    public:
        myfunc(std::string name = "myfunc"): super(name, params(), ttype<node>::get(), *new myBlock()) {
            WRD_I("myfunc(%x) new", this);
        }
        ~myfunc() {
            WRD_I("myfunc(%x) delete", this);
        }

        wbool isRun() const {
            return getBlock().cast<myBlock>()._executed;
        }

        void setLambda(function<wbool(const containable&, const stackFrame&)> lambda) {
            getBlock().cast<myBlock>()._lambda = lambda;
        }

        wbool isSuccess() const {
            return getBlock().cast<myBlock>()._res;
        }

        const wtype& getEvalType() const override {
            return ttype<node>::get();
        }

        const params& getParams() const override { return _params; }
        params& getParams() { return _params; }

    private:
        params _params;
    };

    class nativeFunc : public func {
        WRD(CLASS(nativeFunc, func))

    public:
        nativeFunc(std::string name = "nativeFunc"): super(name) {}

        wbool isRun() const { return _executed; }

        void setLambda(function<wbool(const containable&, const stackFrame&)> lambda) {
            _lambda = lambda;
        }

        wbool isSuccess() const {
            return _res;
        }

        const wtype& getEvalType() const override {
            return ttype<node>::get();
        }

        const params& getParams() const override { return _params; }
        params& getParams() { return _params; }

    protected:
        str _onCastArgs(narr& castedArgs) override {
            _executed = true;
            _res = _lambda(castedArgs, (stackFrame&) wrd::thread::get().getStackFrame());
            return str();
        }

    private:
        function<wbool(const containable&, const stackFrame&)> _lambda;
        params _params;
        wbool _res;
        wbool _executed;
    };
}

TEST_F(packTest, parsePackTest) {
    make(manifest("demo")).parse(R"SRC(
pack demo
    )SRC").shouldParsed(true);
    ASSERT_FALSE(nul(getSubPack()));
    ASSERT_FALSE(nul(getPack().subs()));
    ASSERT_EQ(getPack().subs().len(), 0);
    ASSERT_EQ(getPack().getName(), "demo");
}

TEST_F(packTest, packIsInFrameWhenCallMgdFunc) {
    // check whether pack's subnodes registered into frame when it calls:
    pack testPack(manifest("demo"), packLoadings());
    myfunc f1("foo");

    params& ps = f1.getParams();
    ps.add(new wrd::ref(ttype<wInt>::get(), "age"));
    ps.add(new wrd::ref(ttype<wFlt>::get(), "grade"));
    f1.setLambda([](const auto& contain, const auto& sf) {
        const frame& fr = sf.getCurrentFrame();
        if(nul(fr)) return false;

        // checks pack is in frame:
        myfunc& cast = fr.sub<myfunc>("foo", narr(wInt(), wFlt()));
        if(nul(cast)) return false;

        const params& ps = cast.getParams();
        if(nul(ps)) return false;
        if(ps.len() != 2) return false;
        if(ps[0].getType() != ttype<wInt>()) return false;
        if(ps[1].getName() != "grade") return false;

        // checks args of funcs is in frame:
        wInt& age = fr.sub<wInt>("age");
        if(nul(age)) return false;
        if(age.cast<int>() != 1) return false;

        wFlt& grade = fr.sub("grade").cast<wFlt>();
        if(nul(grade)) return false;
        if(grade.get() < 3.4f || grade.get() > 3.6f) return false;

        return true;
    });

    testPack.subs().add(f1);
    testPack.run("foo", narr(wInt(1), wFlt(3.5f)));
    ASSERT_TRUE(f1.isRun());
    ASSERT_TRUE(f1.isSuccess());
}

TEST_F(packTest, packIsNotInFrameWhenCallNativeFunc) {
    // check whether pack's subnodes not registered into frame when it calls:
    pack testPack(manifest("demo"), packLoadings());
    nativeFunc f1("foo");
    params& ps = f1.getParams();
    ps.add(new wrd::ref(ttype<wInt>::get(), "age"));
    ps.add(new wrd::ref(ttype<wFlt>::get(), "grade"));
    f1.setLambda([](const auto& contain, const auto& sf) {
        const frame& fr = sf.getCurrentFrame();
        if(!nul(fr)) return WRD_E("fr == null"), false;

        return true;
    });
    testPack.subs().add(f1);

    testPack.run("foo", narr(wInt(1), wFlt(3.5f)));
    ASSERT_TRUE(f1.isRun());
    ASSERT_TRUE(f1.isSuccess());
}
