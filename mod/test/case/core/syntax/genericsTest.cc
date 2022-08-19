#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct genericsTest : public namuSyntaxTest {};
}

TEST_F(genericsTest, simpleDefineGenerics) {
    make().parse(R"SRC(
        def object<T>
            T age

        main() void
            sys.con.print("wow")
    )SRC").shouldVerified(true);
}

TEST_F(genericsTest, simpleUseGenerics) {
    make().parse(R"SRC(
        def object<T>
            foo(msg T) void
                sys.con.print(msg)

        main() void
            o := object<str>()
            o.foo("hello generics!")
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    std::string msg = res->cast<std::string>();
    ASSERT_EQ(msg, "hello generics!");
    NAMU_I("msg from generics: %s", msg.c_str());
}
