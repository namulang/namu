#include "../../../syntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct returnExprTest : public syntaxTest {
    };
}

TEST_F(returnExprTest, simpleReturnTypeCheck) {
    make().parse(R"SRC(
        main() int
            return 33
    )SRC").shouldVerified(true);
}

TEST_F(returnExprTest, simpleReturnTypeNegative) {
    make().parse(R"SRC(
        make() int
            return
    )SRC").shouldParsed(true);
    shouldVerified(false);

    mgdFunc& make = getSubPack().sub<mgdFunc>("make");
    ASSERT_FALSE(nul(make));
    blockExpr& blkExp = make.getBlock();
    ASSERT_FALSE(nul(blkExp));
    nucontainer& con = blkExp.subs();
    ASSERT_FALSE(nul(con));
    returnExpr& ret = con.begin().get<returnExpr>();
    ASSERT_FALSE(nul(ret));

    ASSERT_TRUE(ret.getEvalType() == ttype<wVoid>());
}

TEST_F(returnExprTest, returnTypeImplicit) {
    /* TODO: make().parse(R"SRC(
        make() int
            return 3.5
    )SRC").shouldParsed(true);
    shouldVerified(true);*/
}

TEST_F(returnExprTest, implicitReturn) {
    /* TODO: make().parse(R"SRC(
        make() int
            3.5
        )SRC").shouldVerified(true);
    */
}
