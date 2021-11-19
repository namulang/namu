#include "../common/dep.hpp"
#include <iostream>

using namespace wrd;
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

        static inline wbool isRun = false;
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

    narr args;
    args.add(*bridge);
    args.add(new wStr("hello native!"));
    node& func = bridge->sub("say");
    ASSERT_FALSE(nul(func));

    func.run(args);
    ASSERT_TRUE(kniz::isRun);
}

TEST_F(bridgeCPPTest, testHasName) {

    tstr<obj> bridge(tcppBridge<kniz>::def()
        ->func<int, string>("say", &kniz::say));

    ASSERT_TRUE(bridge);
    ASSERT_STREQ(bridge->getName().c_str(), "kniz");
}
