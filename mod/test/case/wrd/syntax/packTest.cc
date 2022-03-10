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

        void setUp() {
            myBlock& blk = getBlock().cast<myBlock>();
            blk._executed = false;
            blk._res = false;
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

/*TEST_F(packTest, packIsLikeObj) {
    pack testPack(manifest("demo"), packLoadings());

    myfunc f1("foo");

    //testPack.subs().add(
}*/
