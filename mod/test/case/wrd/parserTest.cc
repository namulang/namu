#include "../../wrdSyntaxTest.hpp"

using namespace wrd;

struct parserTest : public wrdSyntaxTest {};

TEST_F(parserTest, testHelloWorld) {
    parser p;
    const wchar* stringScript = R"SRC(
        main() void
            console.print("hello world!")
    )SRC";
    std::string script(stringScript);

    tstr<obj> rootBinder = p.parse(script.c_str());
    ASSERT_TRUE(rootBinder);
    rootBinder = p.parse(stringScript);
    ASSERT_TRUE(rootBinder);

    slot s((manifest()));
    scope& shares = (scope&) (((scopes&) s.subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    p.setSlot(s);
    shares.add("hello", new wStr("hello"));
    ASSERT_TRUE(shares.len() == 1);

    p.parse(script.c_str());
    ASSERT_EQ(shares.len(), 2); // @ctor + main: @preCtor doesn't exist.
    p.parse(script.c_str());
    ASSERT_EQ(shares.len(), 3); // add func main on every parse() call.

    ASSERT_TRUE(shares.get<wStr>("hello") == wStr("hello"));
}

TEST_F(parserTest, slotNoOnTray) {
    make().parse(R"SRC(
        main() void
            return
    )SRC");
    shouldVerified(true);

    nbicontainer& shares = (getSlot().subs().begin() + 1).getContainer();
    ASSERT_EQ(shares.len(), 2);
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
    ASSERT_EQ((getSubPack().subs().begin() + 1).getContainer().len(), 2);
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

    nbicontainer& shares = (getSlot().subs().begin() + 1).getContainer();
    ASSERT_EQ(shares.len(), 2);
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
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
