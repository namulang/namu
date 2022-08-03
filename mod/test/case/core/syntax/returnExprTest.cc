#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct returnExprTest : public namuSyntaxTest {};
}

TEST_F(returnExprTest, simpleReturnTypeCheck) {
    make().parse(R"SRC(
        main() int
            return 33
    )SRC").shouldVerified(true);
}

TEST_F(returnExprTest, simpleReturnTypeCheckStr) {
    make().parse(R"SRC(
        main() str
            return "wow"
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
    nucontainer& con = blkExp.getStmts();
    ASSERT_FALSE(nul(con));
    returnExpr& ret = con.begin().get<returnExpr>();
    ASSERT_FALSE(nul(ret));

    ASSERT_TRUE(ret.getEval().getType() == ttype<nVoid>());
}

TEST_F(returnExprTest, implicitReturn) {
    make().parse(R"SRC(
        make() int
            22
    )SRC").shouldVerified(true);
}


TEST_F(returnExprTest, implicitReturnNegative) {
    make().parse(R"SRC(
        make() flt
            "wow"
    )SRC").shouldVerified(false);
}

TEST_F(returnExprTest, implicitReturnShouldNotWorkOnVoid) {
    make().parse(R"SRC(
        main() void
            35
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(returnExprTest, returnLocalVariable) {
    make().parse(R"SRC(
        main() int
            age int
            return age
    )SRC").shouldParsed(true);
    shouldVerified(true);
}

TEST_F(returnExprTest, returnTypeImplicit) {
    /* TODO: make().parse(R"SRC(
        make() int
            return 3.5
    )SRC").shouldParsed(true);
    shouldVerified(true);*/
}

