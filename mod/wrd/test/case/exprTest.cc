#include "../common/dep.hpp"

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

    struct exprTest : public ::testing::Test {
        void SetUp() {
            bridge.bind(tcppBridge<helloWorld>::def()
                ->func("main", &helloWorld::main));
        }

        void TearDown() { helloWorld::isRun = false; }

        tstr<obj> bridge;
    };
}

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
    getExpr exp(&bridge.get(), "main", wtypes({&bridge->getType(), &ttype<wStr>::get()}));
    ASSERT_TRUE(exp.isValid());

    str res = exp.run();
    ASSERT_TRUE(res.isBind());
    ASSERT_TRUE(res.getType() == ttype<node>::get());
    ASSERT_TRUE(res->isSub<func>());
}

TEST_F(exprTest, constructExprInManual) {
    //blockExpr root;
    //root.subs().add(new
}

TEST_F(exprTest, constructExprWithMaker) {
}
