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

namespace {
    struct window {
        int getX() { return 5; }
        int getY() { return _y; }
        void setY(int newY) { _y = newY; }

        int _y;
    };
    struct openGL {
        int init(window* win) {
            return win->getY() + win->getX();
        }
    };
}

TEST_F(bridgeCPPTest, passObj) {
    str winBridge(tcppBridge<window>::def()
            ->func("getX", &window::getX)
            ->func("getY", &window::getY)
            ->func("setY", &window::setY));
    str winOpenGL(tcppBridge<openGL>::def()
            ->func("init", &openGL::init));

    winBridge->run("setY", args{ narr{*new nInt(20)}});
    str res = winOpenGL->run("init", args{ narr{*winBridge}});
    ASSERT_TRUE(res);
    ASSERT_EQ(res->cast<nint>(), 25);
}
