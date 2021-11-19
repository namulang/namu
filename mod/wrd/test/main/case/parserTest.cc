#include "../common/dep.hpp"

using namespace wrd;

TEST(parserTest, testHelloWorld) {
    parser p;
    const wchar* stringScript = "123 ;";
    std::string script(stringScript);

    str rootBinder = p.parse(script.c_str());
    //TODO: ASSERT_TRUE(rootBinder.isBind());

    rootBinder = p.parse(stringScript);
    //TODO: ASSERT_TRUE(rootBinder.isBind());
}
