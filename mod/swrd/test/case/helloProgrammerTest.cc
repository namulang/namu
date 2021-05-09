#include "../common/dep.hpp"

using namespace wrd;
using namespace std;


TEST(helloProgrammerTest, testScript) {
    const std::string script =
        "def programmer\n"
        "   say := 'html is not a programming language!'\n"
        "";

    tstr<swrd::obj> file = swrd::smallWorld::interp(script);
    ASSERT_TRUE(file);

    swrd::obj& programmer = file->sub("programmer");
    ASSERT_FALSE(nul(programmer));

    swrd::obj& say = programmer.sub("say");
    ASSERT_FALSE(nul(say));

    ASSERT_STREQ(say.asStr().c_str(), "html is not a programming language!");
}

TEST(helloProgrammerTest, testScriptEndsWithEOF) {
    const std::string script =
        "def programmer\n"
        "   say := 'html is not a programming language!'\n"
        "   age := 12";

    tstr<swrd::obj> file = swrd::smallWorld::interp(script);
    ASSERT_TRUE(file);

    swrd::obj& programmer = file->sub("programmer");
    ASSERT_FALSE(nul(programmer));

    swrd::obj& say = programmer.sub("say");
    ASSERT_FALSE(nul(say));
    ASSERT_STREQ(say.asStr().c_str(), "html is not a programming language!");

    swrd::obj& age = programmer.sub("age");
    ASSERT_FALSE(nul(age));
    ASSERT_EQ(age.asInt(), 12);
}
