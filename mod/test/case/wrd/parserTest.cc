#include "../../common/dep.hpp"

using namespace wrd;

TEST(parserTest, testHelloWorld) {
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
    narr& tray = pak.subs().cast<narr>();
    ASSERT_FALSE(nul(tray));
    p.setPack(pak);
    tray.add(new wStr("hello"));
    ASSERT_TRUE(tray.len() == 1);

    p.parse(script.c_str());
    // TODO: make AST: ASSERT_TRUE(tray.len() == 2);
    p.parse(script.c_str());
    // TODO: make AST: ASSERT_TRUE(tray.len() == 3);

    ASSERT_TRUE(tray[0].cast<wStr>() == wStr("hello"));
}
