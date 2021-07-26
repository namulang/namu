#include "../common/dep.hpp"

using namespace wrd;

TEST(interpreterTest, testHelloWorld) {
    interpreter interp;
    ASSERT_TRUE(interp.test("123 ;"));
}
