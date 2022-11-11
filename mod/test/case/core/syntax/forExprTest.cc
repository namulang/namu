#include "../../../namuSyntaxTest.hpp"

using namespace namu;
using namespace std;

namespace {
    struct forExprTest : public namuSyntaxTest {};
}

TEST_F(forExprTest, simpleTest) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in {1, 2, 3}
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
                sum = sum + n
            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, simpleTest2) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in {1, 2, 3}
                sum = sum + n
                sys.con.print("sum=" + sum + ", n=" + n + "\n")
            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, testWhatFromFunc) {
    make().parse(R"SRC(
        foo() int[]
            return {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                sys.con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, putAkaMiddleOfLoop) {
    make().parse(R"SRC(
        foo() int[]
            return {1, 2, 3}

        main() int
            sum := 0
            for n in foo()
                sum = sum + n
                aka sys.con
                con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 6);
}

TEST_F(forExprTest, sequenceLoop) {
    make().parse(R"SRC(
        main() int
            sum := 0
            for n in 2..5
                sum = sum + n
                sys.con.print("sum=" + sum + ", n=" + n + "\n")

            return sum
    )SRC").shouldVerified(true);
    str res = run();
    ASSERT_TRUE(res);
    ASSERT_EQ(res.cast<nint>(), 9);
}

TEST_F(forExprTest, validationCheck) {
    make().negative().parse(R"SRC(
        main() str
            for n in {1, 2, 3}
                sys.con.print(n)
    )SRC").shouldParsed(true);
    shouldVerified(false);
}

TEST_F(forExprTest, loopObjects) {
    make().parse(R"SRC(
        def person1
            name := "unknown"
            age := 0
            say() str
                sys.con.print("I'm " + name + " and " + age + " years old.\n")

        main() str
            p1 person1
            p2 := person1()
            p3 := person1()
            p1.name = "Chales"
            p1.age = 36
            p2.name = "Mario"
            p2.age = 45
            p3.name = "Peach"
            p3.age = 44

            sum := ""
            for p in {p1, p2, p3}
                sum = sum + p.say()
            return sum
    )SRC").shouldVerified(true);
    /*str ret = run();
    ASSERT_TRUE(ret);
    std::string answer =    "I'm Chales and 36 years old.\n"
                            "I'm Mario and 45 years old.\n"
                            "I'm Peach and 44 years old.\n";
    std::string msg = ret->cast<std::string>();
    ASSERT_EQ(ret->cast<std::string>(), answer);*/
}

TEST_F(forExprTest, loopObjectsNegative) {
    make().negative().parse(R"SRC(
        def person
            name := "unknown"
            age := 0
            say() str
                sys.con.print("I'm " + name + " and " + age + " years old.\n")

        main() str
            p1 person
            p2 := person()
            p3 := person()
            p1.name = "Chales"
            p1.age = 36
            p2.name = "Mario"
            p2.age = 45
            p3.name = "Peach"
            p3.age = 44

            p1.say()

            sum := ""
            for p in {p1, p2, p3}
                sum = sum + p.say1()
            return sum
    )SRC").shouldVerified(false);
}
