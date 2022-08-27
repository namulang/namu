#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defAssignExprTest : public namuSyntaxTest {};
}

TEST_F(defAssignExprTest, simpleGlobalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age := 5
            return 0
    )SRC").shouldVerified(true);
    scope& owns = (scope&) (((scopes&) getSlot().subs()).getContainer());
    scope& shares = (scope&) (((scopes&) getSlot().subs()).getNext().getContainer());
    ASSERT_FALSE(nul(shares));
    ASSERT_FALSE(nul(owns));
    ASSERT_EQ(owns.len(), 1);
    ASSERT_EQ(shares.len(), 2);

    run();
    ASSERT_EQ(getSubPack().sub<nInt>("age").cast<int>(), 0);
}

TEST_F(defAssignExprTest, simpleLocalDefAssign) {
    // control group.
    make().parse(R"SRC(
        age int // age is age
        main() int // main is also a main
            age = 3
            age := 5
            age = 2
            return 0
    )SRC").shouldVerified(true);
    run();
    ASSERT_EQ(getSubPack().sub("age").cast<int>(), 3);
}

TEST_F(defAssignExprTest, testCircularDependencies) {
    make("holymoly").parse(R"SRC(
        pack holymoly

        a := c
        b := a
        c := b // type can't be defined.

        main() int
            return 0
    )SRC").shouldParsed(true);
    shouldVerified(false);
    // however when runs it, it throws an error.
}

TEST_F(defAssignExprTest, testNearCircularDependencies) {
    make("holymoly").parse(R"SRC(
        pack holymoly

        c := 1 // type can be defined.
        a := c
        b := a

        main() int
            sys.con.print(a as str)
            sys.con.print(b as str)
            return 0
    )SRC").shouldParsed(true);
    shouldVerified(true);
    // however when runs it, it throws an error.
    // because assigning 1 to c will be done after evaluating of assignment of the 'a'.
}

TEST_F(defAssignExprTest, testDefAssign1) {
    make().parse(R"SRC(
        foo() int
            return a = 2

        a := foo() + 5

        main() int
            sys.con.print("a=" + a)
            return 0
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defAssignExprTest, defAssignInObjectRefersInvalidFuncNegative) {
    negative().make().parse(R"SRC(
        aka sys.con c
        nickname := foo()

        foo() str
            c.print("I'm foo!\n")
            return 1 // this is invalid function.

        main() void
            c.print("your nickname is " + nickname)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignInObjectRefersInvalidFuncNegative2) {
    negative().make().parse(R"SRC(
        aka sys.con c
        nickname := boo() // refers the func that doesn't exist.

        foo() str
            c.print("I'm foo!\n")
            return 1 // this is invalid function.

        main() void
            c.print("your nickname is " + nickname)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            sys.con.print("res=" + con)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative2) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            sys.con.print("res=" + con)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defAssignExprTest, defAssignRefersItsIdentifierNegative3) {
    negative().make().parse(R"SRC(
        aka sys.con
        con := con.add(1, 2)

        main() void
            sys.con.print("res=" + con.add(1, 2))
    )SRC").shouldParsed(true);
    shouldVerified(false);
}
