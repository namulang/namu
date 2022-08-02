#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct asExprTest : public namuSyntaxTest {};
}

TEST_F(asExprTest, castInt) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, castInt1) {
    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, castInt2) {
    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, castInt3) {
    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(23)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, castInt4) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(asExprTest, castFlt) {
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

TEST_F(asExprTest, castChar) {
    // implicit casting of char:
    //  -> wbool
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo('a')
    )SRC").shouldParsed(true);
    shouldVerified(false);

    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo('a')
    )SRC").shouldParsed(true);
    shouldVerified(false);

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

TEST_F(asExprTest, castBool) {
    // implicit casting of wbool:
    //  N/A
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

TEST_F(asExprTest, castBool1) {
    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(true)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(asExprTest, castBool2) {
    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(false)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, castBool3) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(true)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(asExprTest, castStr) {
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

TEST_F(asExprTest, manualAsInt) {
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

TEST_F(asExprTest, simpleAsInt1) {
    make().parse(R"SRC(
        foo(age int) void
            main()
        main() void
            foo(23 as int)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, simpleAsInt2) {
    make().parse(R"SRC(
        foo(age flt) void
            main()
        main() void
            foo(23 as flt)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, simpleAsInt3) {
    make().parse(R"SRC(
        foo(age bool) void
            main()
        main() void
            foo(23 as bool)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, simpleAsInt4) {
    make().parse(R"SRC(
        foo(age char) void
            main()
        main() void
            foo(23 as char)
    )SRC").shouldVerified(true);
}

TEST_F(asExprTest, simpleAsInt5) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23 as str)
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(asExprTest, asExprNotAllowed) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23 as foo("wow"))
    )SRC").shouldParsed(false);
}

TEST_F(asExprTest, exprAsAllowed) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(foo("wow") as str)
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(asExprTest, asAs) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23.5 as int as str)
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(asExprTest, asAsNegative) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo(23.5 as str as int)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(asExprTest, AsAllowed) {
    make().parse(R"SRC(
        foo(age str) void
            main()
        main() void
            foo("False" as str) // "False" will cause runtime error
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(asExprTest, reduceTest1) {
    const wtype& it = ttype<wInt>::get();
    const wtype* res = &it.reduce<wFlt>();
    ASSERT_FALSE(nul(res));
    ASSERT_EQ(*res, ttype<wFlt>::get());

    res = &it.reduce<wInt>();
    ASSERT_FALSE(nul(res));
    ASSERT_EQ(*res, ttype<wInt>::get());

    res = &it.reduce<wBool>();
    ASSERT_FALSE(nul(res));
    ASSERT_EQ(*res, ttype<wInt>::get());

    res = &it.reduce<wChar>();
    ASSERT_FALSE(nul(res));
    ASSERT_EQ(*res, ttype<wInt>::get());

    res = &it.reduce<wStr>();
    ASSERT_FALSE(nul(res));
    ASSERT_EQ(*res, ttype<wStr>::get());
}

TEST_F(asExprTest, doubleAs) {
    make().parse(R"SRC(
        foo(idx int) int
           return idx

        main() int
            sys.con.print(foo("54634" as int) as str)
            return 0
    )SRC").shouldVerified(true);
    str ret = run();
    ASSERT_TRUE(ret);
    ASSERT_EQ(ret->cast<int>(), 0);
}

// TODO: make a TC for 'as' nonprimitive types
