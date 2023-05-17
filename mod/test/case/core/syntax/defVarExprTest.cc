#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defVarExprTest : public namuSyntaxTest {};
}

TEST_F(defVarExprTest, simpleDefineVariable) {
    if(make().parse(R"SRC(
        main() void
            age int
            ret
    )SRC").shouldVerified(true)) {
        node& res = getSubPack();
        ASSERT_FALSE(nul(res));

        const mgdFunc& f = res.sub<mgdFunc>("main", narr());
        ASSERT_FALSE(nul(f));
        const narr& stmts = f.getBlock().getStmts();
        ASSERT_FALSE(nul(stmts));
        ASSERT_EQ(stmts.len(), 2);
        const defVarExpr& defVar = stmts[0].cast<defVarExpr>();
        ASSERT_FALSE(nul(defVar));
        ASSERT_EQ(defVar.getName(), "age");
        ASSERT_EQ(defVar.getOrigin().getType(), ttype<nInt>());
    }
}

TEST_F(defVarExprTest, definePackVariableNegative) {
    negative().make().parse(R"SRC(
        name str
        age int
        grade flt
        main() void
            age int
            ret age
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defVarExprTest, definePackVariable2) {
    make().parse(R"SRC(
        name str
        age int
        grade flt
        main() int
            age int
            ret age
    )SRC").shouldParsed(true);
    shouldVerified(true);
    slot& s = getSlot();
    ASSERT_EQ(s.getManifest().name, manifest::DEFAULT_NAME);

    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSlot().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(owns));
    ASSERT_FALSE(nul(shares));
    ASSERT_EQ(owns.len(), 3);
    ASSERT_EQ(shares.len(), 3);
    ASSERT_EQ(s.subAll<baseObj>().len(), 3);
    ASSERT_EQ(s.subAll<mgdFunc>().len(), 1);

    nStr& name = s.sub<nStr>("name");
    ASSERT_FALSE(nul(name));
    ASSERT_EQ(name.get(), "");

    nInt& age = s.sub<nInt>("age");
    ASSERT_FALSE(nul(age));
    ASSERT_EQ(age.get(), 0); // 0 is default value.

    nFlt& grade = s.sub<nFlt>("grade");
    ASSERT_FALSE(nul(grade));
    ASSERT_EQ(grade.get(), 0.0f);
}

/* TODO: TEST_F(defVarExprTest, defineVarWithoutCtorNegative) {
}*/
