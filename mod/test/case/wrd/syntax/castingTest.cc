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
