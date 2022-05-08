#include "../../../wrdSyntaxTest.hpp"

using namespace wrd;
using namespace std;

namespace {
    struct defVarExprTest : public wrdSyntaxTest {};
}

TEST_F(defVarExprTest, simpleDefineVariable) {
    if(make().parse(R"SRC(
        main() void
			age int
			return
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
		const param& p = defVar.getParam();
        ASSERT_EQ(p.getName(), "age");
        ASSERT_EQ(p.getOrigin().getType(), ttype<wInt>());
		ASSERT_TRUE(p.getOrigin());
        ASSERT_EQ(p.getOrigin()->getType(), ttype<wInt>());
    }
}

TEST_F(defVarExprTest, definePackVariableNegative) {
	make().parse(R"SRC(
		name str
		age int
		grade flt
		main() void
			age int
			return age
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
			return age
	)SRC").shouldParsed(true);
	shouldVerified(true);
	pack& pak = getPack();
	ASSERT_EQ(pak.getManifest().name, manifest::DEFAULT_NAME);

	ASSERT_EQ(pak.subs().len(), 4); // 3 variable, 1 func
	ASSERT_EQ(pak.subAll<obj>().len(), 3);
	ASSERT_EQ(pak.subAll<mgdObj>().len(), 1);

	wStr& name = pak.sub<wStr>("name");
	ASSERT_FALSE(nul(name));
	ASSERT_EQ(name.get(), "");

	wInt& age = pak.sub<wInt>("age");
	ASSERT_FALSE(nul(age));
	ASSERT_EQ(age.get(), 0); // 0 is default value.

	wFlt& grade = pak.sub<wFlt>("grade");
	ASSERT_FALSE(nul(grade));
	ASSERT_EQ(grade.get(), 0.0f);
}
