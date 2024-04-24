#include "../../namuSyntaxTest.hpp"

using namespace namu;

struct parserTest : public namuSyntaxTest {};

TEST_F(parserTest, testHelloWorld) {
    repParser p;
    const nchar* stringScript = R"SRC(
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
    shares.add("hello", new nStr("hello"));
    ASSERT_TRUE(shares.len() == 1);

    p.parse(script.c_str());
    ASSERT_EQ(shares.len(), 4); // @ctor*2 + main + 'hello': @preCtor doesn't exist.
    p.parse(script.c_str());
    ASSERT_EQ(shares.len(), 5); // add func main on every parse() call.

    ASSERT_TRUE(shares.get<nStr>("hello") == nStr("hello"));
}

TEST_F(parserTest, slotNoOnTray) {
    make().parse(R"SRC(
        main() void
            ret
    )SRC");
    shouldVerified(true);

    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 0);
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
    scope& shares = (scope&) (((scopes&) getSlot().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_EQ(shares.len(), 3); // 2 builtin func
    ASSERT_EQ(&getSlot().getPack(), &getSubPack());
    func& f = getSubPack().sub<func>("main");
    ASSERT_FALSE(nul(f));
}

TEST_F(parserTest, slotNoOnTrayWithoutMake) {
    // no make() call:
    //  so setPack(new slot(manifest())) won't be called.
    //  but it should works too.
    parse(R"SRC(
        main() void
            ret
    )SRC");
    shouldVerified(true);

    scope& shares = (scope&) (((scopes&) getSlot().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_EQ(getSlot().getManifest().name, manifest::DEFAULT_NAME);
    ASSERT_EQ(&getSlot().getPack(), &getSubPack());
    func& f = getSubPack().sub<func>("main");
    ASSERT_FALSE(nul(f));
}

TEST_F(parserTest, slotNotSpecifiedButCodeSpecifyPackNegative) {
    // make without name:
    //  slot will be generated. but its name is '{default}'.
    negative().make().parse(R"SRC(
        pack demo
        main() void
            ret
    )SRC").shouldParsed(false);
}

TEST_F(parserTest, slotProperlySpecified) {
    // make with name:
    //  pack will be generated and its name is 'demo'.
    make("demo").parse(R"SRC(
        pack demo
        main() void
            ret
    )SRC").shouldParsed(true);
    shouldVerified(true);
}
