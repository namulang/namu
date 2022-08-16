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
