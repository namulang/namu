#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

struct exprTest : public ::testing::Test {
    void SetUp();
    void TearDown();

    tstr<obj> bridge;

    static void setLine(expr& exp, wcnt newLine) {
        exp._lineNum = newLine;
    }
};

namespace {
    struct helloWorld {
        void main(const string msg) {
            cout << "wow, how do you feel? ==> " << msg << "\n";
            isRun = true;
        }

        static inline wbool isRun = false;
    };

}

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
    ASSERT_FALSE(exp.isValid());
    setLine(exp, 1);
    ASSERT_TRUE(exp.isValid());

    str res = exp.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->isSub<func>());
}

TEST_F(exprTest, simpleGetExprNegative) {
    getExpr exp(bridge.get(), "main?", wtypes({&bridge->getType(), &ttype<wStr>::get()}));
    setLine(exp, 1);
    ASSERT_FALSE(exp.isValid());

    getExpr exp2(bridge.get(), "main", wtypes({&ttype<wStr>::get()}));
    setLine(exp2, 1);
    ASSERT_FALSE(exp.isValid());
}

TEST_F(exprTest, simpleRunExpr) {
    runExpr exp1(bridge->sub("main"), narr({&bridge.get(), new wStr("kniz!")}));
    ASSERT_FALSE(exp1.isValid());
    setLine(exp1, 1);
    ASSERT_TRUE(exp1.isValid());

    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->getType() == ttype<wVoid>::get());

    ASSERT_TRUE(helloWorld::isRun);
}

TEST_F(exprTest, simpleRunExprNegative) {
    runExpr exp1(bridge->sub("main"), narr({&bridge.get(), new wVoid()}));
    setLine(exp1, 1);
    ASSERT_FALSE(exp1.isValid());

    ASSERT_FALSE(helloWorld::isRun);

    str res = exp1.run();
    ASSERT_FALSE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_FALSE(helloWorld::isRun);
}

TEST_F(exprTest, constructExprInManual) {
    //blockExpr root;
    //root.subs().add(new
}

TEST_F(exprTest, constructExprWithMaker) {
}
