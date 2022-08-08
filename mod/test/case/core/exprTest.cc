#include "../../namuTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct helloWorld {
        void main(const string msg) {
            cout << "wow, how do you feel? ==> " << msg << "\n";
            isRun = true;
        }

        static inline nbool isRun = false;
    };
}

struct exprTest : public namuTest {
    void SetUp();
    void TearDown();

    tstr<obj> bridge;

    static void setLine(expr& exp, ncnt row, ncnt col) {
        exp._pos = {row, col};
    }
};

void exprTest::SetUp() {
    namuTest::SetUp();
    bridge.bind(tcppBridge<helloWorld>::def()
        ->func("main", &helloWorld::main));
}

void exprTest::TearDown() {
    namuTest::TearDown();
    helloWorld::isRun = false;
}

TEST_F(exprTest, standbyHelloWorldBridgeObj) {
    ASSERT_TRUE(bridge.isBind());

    tstr<nStr> msg(new nStr());
    args a(*bridge, {msg.get()});

    node& mainFunc = bridge->sub("main", a);
    ASSERT_FALSE(nul(mainFunc));
    ASSERT_TRUE(mainFunc.canRun(a));
    ASSERT_FALSE(mainFunc.canRun(args(*bridge, {*bridge, *msg})));
    ASSERT_FALSE(helloWorld::isRun);
    str res = mainFunc.run(a);
    ASSERT_FALSE(res.isBind());
    res = bridge->run("main", a);
    ASSERT_TRUE(res.isBind());
    res = bridge->run("main", args({*msg}));
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<nVoid>::get());
    ASSERT_TRUE(helloWorld::isRun);
}

TEST_F(exprTest, simpleGetExpr) {
    getExpr exp(bridge.get(), "main", narr(*new nStr()));
    errReport rep;
    verifier veri;
    veri.setReport(rep).verify(exp);
    /*TODO: uncomment this
    ASSERT_TRUE(rep); // should have some errors.*/
    setLine(exp, 1, 1);

    rep.rel();
    ASSERT_FALSE(rep);
    veri.verify(exp);
    ASSERT_FALSE(rep);

    str res = exp.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->isSub<func>());
}

TEST_F(exprTest, simpleGetExprNegative) {
    getExpr exp(bridge.get(), "main?", narr(*new nStr()));
    setLine(exp, 1, 1);
    errReport rep;
    verifier veri;
    veri.setReport(rep).verify(exp);
    ASSERT_TRUE(rep); // should have some errs.

    getExpr exp2(bridge.get(), "main", narr(*new nStr()));
    setLine(exp2, 1, 1);
    rep.rel();
    veri.verify(exp);
    ASSERT_TRUE(rep);
}

TEST_F(exprTest, simpleRunExprWithoutMeObjNegative) {
    runExpr exp1(bridge->sub("main"), narr(*new nStr("kniz!")));
    errReport rep;
    verifier veri;
    veri.setReport(rep).verify(exp1);
    /*TODO: expr parser didn't put col & row on AST yet
     *      uncomment these after the patch
    ASSERT_TRUE(rep);*/

    setLine(exp1, 1, 1);
    rep.rel();
    veri.setReport(rep).verify(exp1);
    ASSERT_TRUE(rep);
}

TEST_F(exprTest, simpleRunExpr) {
    runExpr exp1(*bridge, "main", narr(*new nStr("kniz!")));
    errReport rep;
    verifier veri;
    veri.setReport(rep).verify(exp1);
    /*TODO: expr parser didn't put col & row on AST yet
     *      uncomment these after the patch
    ASSERT_TRUE(rep);*/

    setLine(exp1, 1, 1);
    rep.rel();
    veri.setReport(rep).verify(exp1);
    ASSERT_FALSE(rep);
    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<nVoid>::get());

    ASSERT_TRUE(helloWorld::isRun);
}

TEST_F(exprTest, simpleRunExprNegative) {
    runExpr exp1(bridge->sub("main"), narr());
    setLine(exp1, 1, 1);
    errReport rep;
    verifier veri;
    veri.setReport(rep).verify(exp1);
    ASSERT_TRUE(rep);

    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_FALSE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_FALSE(helloWorld::isRun);
}

TEST_F(exprTest, constructExprInManual) {
    runExpr r(*bridge, "main", narr(*new nStr("kniz!")));
    setLine(r, 1, 1);

    str res = r.run();
    ASSERT_TRUE(res);
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<nVoid>::get());
}

TEST_F(exprTest, defVarExpr) {
    // TODO:
}
