#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct defObjExprTest : public namuSyntaxTest {};
}

TEST_F(defObjExprTest, simpleDefineObject) {
    make().parse(R"SRC(
        def A
            foo() void
                print("hello")
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defObjExprTest, simpleDefineObject2) {
    make().parse(R"SRC(
        def A
            foo() void
                print("hello")
        main() void
            a A
            a.foo()
    )SRC").shouldVerified(true);
    run();
}

TEST_F(defObjExprTest, simpleDefineObjectNegative) {
    negative().make().parse(R"SRC(
        def A
            foo() void
                print("hello")
        main() void
            a B
            a.foo()
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(defObjExprTest, assignMemberVariable) {
    make().parse(R"SRC(
        def obj
            index := 5

        main() int
            o := obj()
            o.index = 2
            print(o.index as str)
            o.index
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 2);
}

TEST_F(defObjExprTest, make2Objects) {
    make().parse(R"SRC(
        def obj
            name := ""
            age int

        main() str
            o1 := obj()
            o1.name = "Chales"
            o1.age = 36
            o2 := obj()
            o2.name = "kniz"
            o2.age = 22

            ret o1.name + o2.name + o1.age as str + o2.age as str
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    std::string answer = "Chaleskniz3622";
    ASSERT_EQ(res.cast<std::string>(), answer);
}

TEST_F(defObjExprTest, manipulate2Origin) {
    make().parse(R"SRC(
        def obj
            name := ""
            age int

        main() str
            o1 obj
            o1.name = "Chales"
            o1.age = 36
            o2 obj
            o2.name = "kniz"
            o2.age = 22

            ret o1.name + o2.name + o1.age as str + o2.age as str
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    std::string answer = "Chaleskniz3622";
    ASSERT_EQ(res.cast<std::string>(), answer);
}

TEST_F(defObjExprTest, objAsParameter) {
    make().parse(R"SRC(
        def person
            name := "default"

        foo(p person) str
            p.name

        main() str
            foo(person())
    )SRC").shouldVerified(true);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "default");
}

TEST_F(defObjExprTest, incompleteObjNegative) {
    make().parse(R"SRC(
        def person
            name := "default"

        foo(p person) str
            p.name

        main() str
            foo(person)
    )SRC").shouldVerified(false);

    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<std::string>(), "default");
}
