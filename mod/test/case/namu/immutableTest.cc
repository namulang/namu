#include "../../namuTest.hpp"

using namespace namu;

namespace {

    struct myObj : public obj {
        WRD(CLASS(myObj, obj))

    public:
        myObj(int newVal = 0): val(newVal) {}

        int val;

        wbool _onSame(const typeProvidable& rhs) const override {
            const myObj& cast = (const myObj&) rhs;
            return val == cast.val;
        }
    };

    class myfunc : public mgdFunc {
        WRD(CLASS(myfunc, mgdFunc))

        class myBlock : public blockExpr {
            WRD(CLASS(myBlock, blockExpr))

        public:
            str run(const ucontainable& args) override {
                WRD_I("hello world!");
                _executed = true;

                if(_lambda)
                    _res = _lambda(args, (frames&) namu::thread::get().getFrames());
                return str();
            }

            void setLambda(std::function<wbool(const ucontainable&, const frames&)> lambda) {
                _lambda = lambda;
            }

            std::function<wbool(const ucontainable&, const frames&)> _lambda;
            wbool _res;
            wbool _executed;
        };

    public:
        myfunc(): super(params(), *new wVoid(), *new myBlock()) {
            WRD_I("myfunc(%x) new", this);
        }
        ~myfunc() {
            WRD_I("myfunc(%x) delete", this);
        }

        wbool isRun() const {
            return getBlock().cast<myBlock>()._executed;
        }

        void setLambda(std::function<wbool(const ucontainable&, const frames&)> lambda) {
            getBlock().cast<myBlock>()._lambda = lambda;
        }

        wbool isSuccess() const {
            return getBlock().cast<myBlock>()._res;
        }

        const node& getRet() const override {
            static wVoid inner;
            return inner;
        }

        const params& getParams() const override { return _params; }
        params& getParams() { return _params; }

    private:
        params _params;
    };
}

struct immutableTest : public namuTest {
    frames& getFrames() {
        return (frames&) thread::get().getFrames();
    }

    void SetUp() {
        getFrames().add(new frame());
    }

    void TearDown() {
        thread::get().rel();
    }

    scopeStack& getScopeStack(frame& fr) {
        return fr._local;
    }
};

TEST_F(immutableTest, testImmutablePositive) {
    tstr<wFlt> r1(new wFlt(1.0f));
    str r2 = r1;
    ASSERT_TRUE(r1);
    ASSERT_TRUE(r2);
    ASSERT_EQ(*r1, *r2);

    r1->get() = 0.5f;
    ASSERT_EQ(*r1, *r2);

    param r3("", *r1);
    ASSERT_FALSE(nul(r3.getOrigin()));
    ASSERT_EQ(r3.getOrigin().getType(), ttype<wFlt>::get());

    scope s;
    s.add("r1", *r1);
    const wFlt& cast = s["r1"].cast<wFlt>();
    ASSERT_FALSE(nul(cast));
    ASSERT_NE(&r1.get(), &cast);
    ASSERT_EQ(*r1, cast);
}

TEST_F(immutableTest, testImmutableNegative) {
    str r1(new myObj(1));
    str r2 = r1;
    ASSERT_TRUE(r1);
    ASSERT_TRUE(r2);
    ASSERT_EQ(*r1, *r2);

    r1->cast<myObj>().val = 2;
    ASSERT_EQ(*r1, *r2);

    nmap m;
    m.add("r1", *r1);
    const myObj& cast = m["r1"].cast<myObj>();
    ASSERT_FALSE(nul(cast));
    ASSERT_EQ(&r1.get(), &cast);
    ASSERT_EQ(r1->cast<myObj>().val, cast.val);
}

TEST_F(immutableTest, testFrameImmutability) {
    myObj o1;
    o1.subs().add("age", new wInt(18));
    node& age = o1.subs().begin().getVal();

    myfunc mf;
    mf.setLambda([&](const ucontainable&, const frames&) {
        frame& fr = (frame&) namu::thread::get().getNowFrame();
        // test assign:
        auto e = fr.subs().iterate("age");
        if(e.isEnd()) return WRD_E("there is no key"), false;

        fr.pushLocal("age1", age);

        wInt& age1 = fr.sub<wInt>("age1");
        if(age1 != age) return WRD_E("age1 != age"), false;
        if(&age1 == &age) return WRD_E("address of age1 and age are different"), false;

        return true;
    });

    o1.subs().add("foo", mf);
    o1.run("foo", narr());
    ASSERT_TRUE(mf.isSuccess());
}
