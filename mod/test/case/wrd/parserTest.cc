#include "../../wrdSyntaxTest.hpp"

using namespace wrd;

struct parserTest : public wrdSyntaxTest {};

TEST_F(parserTest, testHelloWorld) {
    parser p;
    const wchar* stringScript = R"SRC(
        main()
            console.print("hello world!")
    )SRC";
    std::string script(stringScript);

    tstr<obj> rootBinder = p.parse(script.c_str());
    ASSERT_TRUE(rootBinder);
    // TODO: make AST: ASSERT_TRUE(rootBinder->subs().len() == 1);
    rootBinder = p.parse(stringScript);
    ASSERT_TRUE(rootBinder);
    // TODO: make AST: ASSERT_TRUE(rootBinder->subs().len() == 2);

    slot s((manifest()));
    nbicontainer& tray = s.subs();
    ASSERT_FALSE(nul(tray));
    p.setSlot(s);
    tray.add("hello", new wStr("hello"));
    ASSERT_TRUE(tray.len() == 1);

    p.parse(script.c_str());
    ASSERT_TRUE(tray.len() == 3); // hello + @ctor + main: @preCtor doesn't exist.
    // TODO: make AST: ASSERT_TRUE(tray.len() == 2);
    p.parse(script.c_str());
    ASSERT_TRUE(tray.len() == 4); // add func main on every parse() call.
    // TODO: make AST: ASSERT_TRUE(tray.len() == 3);

    ASSERT_TRUE(tray.get<wStr>("hello") == wStr("hello"));
}

TEST_F(parserTest, slotNoOnTray) {
    make().parse(R"SRC(
        main() void
            return
    )SRC");
    shouldVerified(true);

    ASSERT_EQ(getSlot().subs().len(), 2);
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
    ASSERT_EQ(getSubPack().subs().len(), 2);
    ASSERT_EQ(&getSlot().getPack(), &getSubPack());
    mgdFunc& f = getSubPack().sub<mgdFunc>("main");
    ASSERT_FALSE(nul(f));
}

TEST_F(parserTest, slotNoOnTrayWithoutMake) {
    // no make() call:
    //  so setPack(new slot(manifest())) won't be called.
    //  but it should works too.
    parse(R"SRC(
        main() void
            return
    )SRC");
    shouldVerified(true);

    ASSERT_EQ(getSlot().subs().len(), 2);
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
    ASSERT_EQ(getSubPack().subs().len(), 2);
    ASSERT_EQ(&getSlot().getPack(), &getSubPack());
    mgdFunc& f = getSubPack().sub<mgdFunc>("main");
    ASSERT_FALSE(nul(f));
}

TEST_F(parserTest, slotNotSpecifiedButCodeSpecifyPackNegative) {
    // make without name:
    //  slot will be generated. but its name is '{default}'.
    make().parse(R"SRC(
        pack demo
        main() void
            return
    )SRC").shouldParsed(false);
}

TEST_F(parserTest, slotProperlySpecified) {
    // make with name:
    //  pack will be generated and its name is 'demo'.
    make("demo").parse(R"SRC(
        pack demo
        main() void
            return
    )SRC").shouldParsed(true);
    shouldVerified(true);
}
