#include "../../wrdTest.hpp"

using namespace wrd;

struct parserTest : public wrdTest {};

TEST_F(parserTest, testHelloWorld) {
    parser p;
    const wchar* stringScript = R"SRC(
        main()
            console.print("hello world!")
    )SRC";
    std::string script(stringScript);

    tstr<pack> rootBinder = p.parse(script.c_str());
    ASSERT_TRUE(rootBinder);
    // TODO: make AST: ASSERT_TRUE(rootBinder->subs().len() == 1);
    rootBinder = p.parse(stringScript);
    ASSERT_TRUE(rootBinder);
    // TODO: make AST: ASSERT_TRUE(rootBinder->subs().len() == 2);

    pack pak((manifest()), (packLoadings()));
    nbicontainer& tray = pak.subs();
    ASSERT_FALSE(nul(tray));
    p.setPack(pak);
    tray.add("hello", new wStr("hello"));
    ASSERT_TRUE(tray.len() == 1);

    p.parse(script.c_str());
    // TODO: make AST: ASSERT_TRUE(tray.len() == 2);
    p.parse(script.c_str());
    // TODO: make AST: ASSERT_TRUE(tray.len() == 3);

    ASSERT_TRUE(tray.begin()->cast<wStr>() == wStr("hello"));
}
