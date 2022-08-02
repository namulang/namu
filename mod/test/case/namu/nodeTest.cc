#include "../../namuTest.hpp"

using namespace namu;
using namespace std;

struct nodeTest : public namuTest {};

namespace {
    class myFunc : public mgdFunc {
        WRD(CLASS(myFunc, mgdFunc))

    public:
        myFunc(): super(params(), new wVoid()) {}

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

        const node& getRet() const override {
            static wVoid inner;
            return inner;
        }

        const params& getParams() const override {
            static params inner;
            return inner;
        }

    private:
        wbool _executed;
    };

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

    class food : public obj {
        WRD(CLASS(food, obj))

    public:
        food(string newName, int newCalorie): name(newName), calorie(newCalorie) {}

        string name;
        int calorie;
    };

    class chef : public obj {

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
        WRD(CLASS(chef, obj, myType))

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
    WRD_DI("func.tag.chkId=%d", func.getBindTag().getId().chkN);

    obj.subs().add("myFunc", func);
    myFunc funcOffunc;
    func.subs().add("funcOfFunc", funcOffunc);

    WRD_DI("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_DI("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // when:
    frameEmulator.bind(obj.subs());
    //  push another:
    scopes* chnOffunc = scopes::wrap(func.subs());
    chnOffunc->link(*frameEmulator);
    frameEmulator.bind(*chnOffunc);

    WRD_DI("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_DI("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    // then:
    ASSERT_EQ(chnOffunc->len(), 2);
    ASSERT_EQ(chnOffunc->len(), 2);
    ASSERT_EQ(chnOffunc->len(), 2);

    int n=0;
    for(const auto& elem : *chnOffunc)
        WRD_DI("[%d]=%s", n++, elem.getType().getName().c_str());

    WRD_DI("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_DI("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);

    ASSERT_EQ(n, 2);
    WRD_DI("func.tag.chkId=%d", func.getBindTag().getId().chkN);
    WRD_DI("funcOffunc.tag.chkId=%d", funcOffunc.getBindTag().getId().chkN);
}

TEST_F(nodeTest, testManualNativefuncCall) {
    // prepare:
    myFunc func;

    myObj obj;
    obj.subs().add("myFunc", func);

    narr args;
    narr subs = ((const myObj&) obj).subAll("myFunc", args);
    ASSERT_EQ(subs.len(), 1);
    ASSERT_TRUE(subs[0].canRun(args));

    // when:
    func.setUp();
    subs[0].run(args);
    ASSERT_TRUE(func.isRun());
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

