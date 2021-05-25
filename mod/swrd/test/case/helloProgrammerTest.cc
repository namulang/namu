#include "../common/dep.hpp"

using namespace wrd;
using namespace std;


TEST(helloProgrammerTest, testScript) {
    const std::string script =
        "def programmer\n"
        "   say := 'html is not a programming language!'\n"
        "";

    tstr<sobj> file = swrd::interp(script);
    ASSERT_TRUE(file);

    sobj& programmer = file->sub("programmer");
    ASSERT_FALSE(nul(programmer));

    sobj& say = programmer.sub("say");
    ASSERT_FALSE(nul(say));

    ASSERT_STREQ(say.asStr().c_str(), "html is not a programming language!");
}

TEST(helloProgrammerTest, testScriptEndsWithEOF) {
    const std::string script =
        "def programmer\n"
        "   say := 'html is not a programming language!'\n"
        "   age := 12";

    tstr<sobj> file = swrd::interp(script);
    ASSERT_TRUE(file);

    sobj& programmer = file->sub("programmer");
    ASSERT_FALSE(nul(programmer));

    sobj& say = programmer.sub("say");
    ASSERT_FALSE(nul(say));
    ASSERT_STREQ(say.asStr().c_str(), "html is not a programming language!");

    sobj& age = programmer.sub("age");
    ASSERT_FALSE(nul(age));
    ASSERT_EQ(age.asInt(), 12);
}

TEST(helloProgrammerTest, testScriptWithPackScope) {
    const std::string script =
        "say := 'html is not a programming language!'\n"
        "age := 12\n"
        "def ramen\n"
        " name := 'doshirak'\n";

    tstr<sobj> file = swrd::interp(script);
    ASSERT_TRUE(file);

    sobj& say = file->sub("say");
    ASSERT_FALSE(nul(say));
    ASSERT_STREQ(say.asStr().c_str(), "html is not a programming language!");

    sobj& ramen = file->sub("ramen");
    ASSERT_FALSE(nul(ramen));

    {
        sobj& name = ramen.sub("name");
        ASSERT_FALSE(nul(name));
        ASSERT_STREQ(name.asStr().c_str(), "doshirak");
    }
}

TEST(helloProgrammerTest, testNullObjNegative) {

    const std::string script =
        "say := 'html is not a programming language!'\n"
        "age := 12\n"
        "def ramen\n"
        " name := 'doshirak'\n";

    tstr<sobj> file = swrd::interp(script);
    ASSERT_TRUE(file);

    sobj& notExist = file->sub("dogecoin");
    ASSERT_FALSE(notExist);
    ASSERT_STREQ(notExist.asStr().c_str(), "");
    ASSERT_EQ(notExist.asInt(), 0);
    ASSERT_EQ(notExist.asBool(), false);
    ASSERT_EQ(notExist.asChar(), '\0');
}
