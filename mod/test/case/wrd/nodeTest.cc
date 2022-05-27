#include "../../wrdTest.hpp"

using namespace wrd;
using namespace std;

struct nodeTest : public wrdTest {};

namespace {
    class myFunc : public mgdFunc {
        WRD(CLASS(myFunc, mgdFunc))

    public:
        myFunc(): super(params(), ttype<node>::get()) {}

        void setUp() {
            _executed = false;
        }

        str run(const ucontainable& args) override {
            WRD_I("hello world!");
            _executed = true;
            return str();
        }

        wbool isRun() const {
            return _executed;
        }

        const wtype& getRetType() const override {
            return ttype<node>::get();
        }

        const params& getParams() const override {
            static params inner;
            if(inner.len() == 0)
                inner.add(new param("", ttype<obj>::get()));

            return inner;
        }

    private:
        wbool _executed;
    };

    struct myObj : public mgdObj {
        WRD(CLASS(myObj, mgdObj))

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

    class food : public mgdObj {
        WRD(CLASS(food, mgdObj))

    public:
        food(string newName, int newCalorie): name(newName), calorie(newCalorie) {}

        string name;
        int calorie;

        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }
    };

    class chef : public mgdObj {

        class myType : public wtype {
            WRD_DECL_ME(myType, wtype);

        protected:
            const ases& _getImpliAses() const override {
                static ases* inner = nullptr;
                if(inner) return *inner;

                inner = new ases();
                struct tofood : public tas<food> {
                    str as(const node& it, const type& to) const override {
                        const chef& chef1 = it.cast<chef>();
                        if(nul(chef1)) return str();

                        return str(new food(chef1.foodName, chef1.foodCalorie));
                    }
                };
                inner->add(new tofood());

                return *inner;
            }
        };
        WRD(CLASS(chef, mgdObj, myType))

        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }

    public:
        string foodName;
        int foodCalorie;
    };
}

TEST_F(nodeTest, testManuallyMakeNodeStructure) {
    // prepare:
    tstr<scopes> frameEmulator;
    myObj obj;
    myFunc func;
    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);

    obj.subs().add("myFunc", func);
    myFunc funcOffunc;
    func.subs().add("funcOfFunc", funcOffunc);

    WRD_E("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_E("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // when:
    frameEmulator.bind(obj.subs());
    //  push another:
    scopes* chnOffunc = scopes::wrap(func.subs());
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

TEST_F(nodeTest, testManualNativefuncCall) {
    // prepare:
    myFunc func;

    myObj obj;
    obj.subs().add("myFunc", func);

    narr args;
    args.add(obj);
    narr subs = ((const myObj&) obj).subAll("myFunc", args);
    ASSERT_EQ(subs.len(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
}

TEST_F(nodeTest, testImmutablePositive) {
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
    ASSERT_EQ(r3.getOrigin().cast<wFlt>().get(), r1->get());

    scope s;
    s.add("r1", *r1);
    const wFlt& cast = s["r1"].cast<wFlt>();
    ASSERT_FALSE(nul(cast));
    ASSERT_NE(&r1.get(), &cast);
    ASSERT_EQ(*r1, cast);
}

TEST_F(nodeTest, testImmutableNegative) {
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

TEST_F(nodeTest, testchefImplicitCastTofood) {
    // prepare:
    const string expectName = "HealthPotion";
    const int expectCalorie = 350;
    chef chef;
    chef.foodName = expectName;
    chef.foodCalorie = expectCalorie;

    const wtype& chefType = chef.getType();
    ASSERT_TRUE(chefType.isImpli<food>());
    tstr<food> cast = chef.asImpli<food>();
    ASSERT_TRUE(cast);

    EXPECT_EQ(cast->name, expectName);
    EXPECT_EQ(cast->calorie, expectCalorie);
}

TEST_F(nodeTest, ShouldNotSameNameVariableIntoSubs) {
    chef c;
    ASSERT_EQ(c.subs().len(), 0);
    c.subs().add("age", new wInt(22));
    ASSERT_EQ(c.subs().len(), 1);
    ASSERT_EQ(c.sub<wInt>("age").get(), 22);
    errReport rpt;
    verifier v;
    v.setReport(rpt).verify(c);
    ASSERT_FALSE(rpt);

    c.subs().add("age1", new wInt(22));
    ASSERT_EQ(c.subs().len(), 2);
    ASSERT_EQ(c.subAll<wInt>("age1")[0].get(), 22);
    v.verify(c);
    ASSERT_FALSE(rpt);

    c.subs().add("age", new wInt(23));
    ASSERT_EQ(c.subs().len(), 3);
    ASSERT_EQ(c.subAll<wInt>("age").len(), 2);
    v.verify(c);
    ASSERT_TRUE(rpt);
}

