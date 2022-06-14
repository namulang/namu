#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct castingTest : public wrdSyntaxTest {};
}

TEST_F(castingTest, castInt) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castFlt) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(23.0)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(23.0)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(23.0)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(23.0)
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23.0)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castChar) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo('a')
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo('a')
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo('a')
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo('a')
    )SRC").shouldVerified(true);

    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo('a')
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castBool) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(false)
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(false)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castBool1) {
    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(true)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castBool2) {
    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(false)
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, castBool3) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(true)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(castingTest, castStr) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo("wow")
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo("wow")
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo("wow")
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo("wow")
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo("wow")
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, manualAsInt) {
    wInt a = 55;
    str as = a.as<wStr>();
    ASSERT_TRUE(as);
    ASSERT_EQ(as->cast<std::string>(), "55");

    wFlt b(3.5);
    as = b.as<wInt>();
    ASSERT_TRUE(as);
    ASSERT_EQ(as->cast<wint>(), (int) 3.5);

    as = wStr("False").as<wBool>();
    ASSERT_FALSE(as);
    as = wStr("false").as<wBool>();
    ASSERT_TRUE(as);
    ASSERT_FALSE(as->cast<wbool>()); // false -> false
    as = wFlt(0.1f).as<wBool>();
    ASSERT_TRUE(as);
    ASSERT_EQ(as->cast<wbool>(), (bool) 0.1f); // 0 -> false

    as = wFlt(1.1f).as<wBool>();
    ASSERT_TRUE(as);
    ASSERT_TRUE(as->cast<wbool>()); // except for 0 -> true
}

TEST_F(castingTest, simpleAsInt1) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(23 as int)
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, simpleAsInt2) {
    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(23 as flt)
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, simpleAsInt3) {
    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(23 as bool)
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, simpleAsInt4) {
    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(23 as char)
    )SRC").shouldVerified(true);
}

TEST_F(castingTest, simpleAsInt5) {
    /* TODO: uncomment this after add asExpr
     * make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23 as str)
    )SRC").shouldParsed(true);
    shouldVerified(true); */
}
