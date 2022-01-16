#include "../../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct helloWorld {
        void main(const string msg) {
            cout << "wow, how do you feel? ==> " << msg << "\n";
            isRun = true;
        }

        static inline wbool isRun = false;
    };
}

struct exprTest : public ::testing::Test {
    void SetUp();
    void TearDown();

    tstr<obj> bridge;

    static void setLine(expr& exp, wcnt row, wcnt col) {
        exp._pos = {row, col};
    }
};

void exprTest::SetUp() {
    bridge.bind(tcppBridge<helloWorld>::def()
        ->func("main", &helloWorld::main));
}

void exprTest::TearDown() { helloWorld::isRun = false; }

TEST_F(exprTest, standbyHelloWorldBridgeObj) {
    ASSERT_TRUE(bridge.isBind());

    tstr<wStr> msg(new wStr());
    narr args {&bridge.get(), &msg.get()};

    node& mainFunc = bridge->sub("main", args);
    ASSERT_FALSE(nul(mainFunc));
    ASSERT_TRUE(mainFunc.canRun(args));
    ASSERT_FALSE(mainFunc.canRun(wtypes({&msg->getType()})));
    ASSERT_TRUE(mainFunc.canRun(wtypes({&bridge->getType(), &msg->getType()})));
    ASSERT_FALSE(helloWorld::isRun);
    str res = mainFunc.run(args);
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<wVoid>::get());
    ASSERT_TRUE(helloWorld::isRun);
}

TEST_F(exprTest, simpleGetExpr) {
    getExpr exp(bridge.get(), "main", wtypes({&bridge->getType(), &ttype<wStr>::get()}));
    errReport rep;
    verifier veri;
    veri.verify(exp, rep);
    ASSERT_TRUE(rep); // should have some errors.
    setLine(exp, 1, 1);

    rep.rel();
    ASSERT_FALSE(rep);
    veri.verify(exp, rep);
    ASSERT_FALSE(rep);

    str res = exp.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->isSub<func>());
}

TEST_F(exprTest, simpleGetExprNegative) {
    getExpr exp(bridge.get(), "main?", wtypes({&bridge->getType(), &ttype<wStr>::get()}));
    setLine(exp, 1, 1);
    errReport rep;
    verifier veri;
    veri.verify(exp, rep);
    ASSERT_TRUE(rep); // should have some errs.

    getExpr exp2(bridge.get(), "main", wtypes({&ttype<wStr>::get()}));
    setLine(exp2, 1, 1);
    rep.rel();
    veri.verify(exp, rep);
    ASSERT_TRUE(rep);
}

TEST_F(exprTest, simpleRunExpr) {
    runExpr exp1(bridge->sub("main"), narr({&bridge.get(), new wStr("kniz!")}));
    errReport rep;
    verifier veri;
    veri.verify(exp1, rep);
    ASSERT_TRUE(rep);

    setLine(exp1, 1, 1);
    rep.rel();
    veri.verify(exp1, rep);
    ASSERT_FALSE(rep);

    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<wVoid>::get());

    ASSERT_TRUE(helloWorld::isRun);
}

TEST_F(exprTest, simpleRunExprNegative) {
    runExpr exp1(bridge->sub("main"), narr({&bridge.get(), new wVoid()}));
    setLine(exp1, 1, 1);
    errReport rep;
    verifier veri;
    veri.verify(exp1, rep);
    ASSERT_TRUE(rep);

    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_FALSE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_FALSE(helloWorld::isRun);
}

TEST_F(exprTest, constructExprInManual) {
	getExpr g(bridge.get(), "main", wtypes({&bridge->getType(), &ttype<wStr>::get()}));
	setLine(g, 1, 1);
	runExpr r(g, narr({&bridge.get(), new wStr("kniz!")}));
	setLine(r, 1, 1);

	str res = r.run();
	ASSERT_TRUE(res);
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<wVoid>::get());
}

TEST_F(exprTest, constructExprWithMaker) {
	exprMaker maker;
	tstr<runExpr> r = maker.addRow().make<runExpr>(
		*maker.make<getExpr>(bridge.get(), "main", wtypes({&bridge->getType(), &ttype<wStr>::get()})),
		narr({&bridge.get(), new wStr("kniz!")})
	);

	ASSERT_EQ(r->getPos().row, 1);

	str res = r->run();
	ASSERT_TRUE(res);
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<wVoid>::get());
}
