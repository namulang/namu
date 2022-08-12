#include "../../common/dep.hpp"
#include <iostream>

using namespace namu;
using namespace std;

namespace {
    struct kniz {
        void say() {
            cout << "I'm kniz. have lived in Korea.\n";
            isRun = true;
        }
        int say(string msg) {
            cout << "They let me say '" << msg << "'\n";
            isRun = true;
            return 0;
        }
        bool sayCharPtr(const char* msg) {
            cout << "Oh, it's charactor pointer. Of course I can say it without problem like '" << msg << "'. were you suprise?\n";
            return isRun = true;
        }

        static inline nbool isRun = false;
    };

    struct bridgeCPPTest : public ::testing::Test {
        void TearDown() {
            kniz::isRun = false;
        }
    };
}

TEST_F(bridgeCPPTest, testNormalWrapping) {
    tstr<tcppBridge<kniz>> bridge(tcppBridge<kniz>::def()
        ->func<int, string>("say", &kniz::say));
        // TODO: how to handle void return & void parameter
        //.func<void, void>(&kniz::say);

    node& func = bridge->sub("say");
    ASSERT_FALSE(nul(func));

    bridge->run("say", args(narr{*new nStr("hello native!")}));
    ASSERT_TRUE(kniz::isRun);
}

TEST_F(bridgeCPPTest, testFuncDoesntHaveObjNegative) {
    tstr<tcppBridge<kniz>> bridge(tcppBridge<kniz>::def()
        ->func<int, string>("say", &kniz::say));
        // TODO: how to handle void return & void parameter
        //.func<void, void>(&kniz::say);

    args a;
    a.add(*bridge);
    a.add(new nStr("hello native!"));
    bridge->run("say", args(*bridge, narr{*bridge, *new nStr("hello native!")}));
    ASSERT_FALSE(kniz::isRun);

    // bridge set its address to args's setMe()
    bridge->run("say", args(narr{*new nStr("hello native!")}));
    ASSERT_TRUE(kniz::isRun);
}

TEST_F(bridgeCPPTest, testHasName) {
    tstr<obj> bridge(tcppBridge<kniz>::def()
        ->func<int, string>("say", &kniz::say));
    nmap m;
    ASSERT_TRUE(bridge);
    m.add("kniz", *bridge);

    func& say = m["kniz"]["say"].cast<func>();
    ASSERT_FALSE(nul(say));
}
