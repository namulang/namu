#include "../common/dep.hpp"

using namespace wrd;

TEST(parserTest, testHelloWorld) {
    parser p;
    str rootBinder = p.parseBuffer("123 ;");
    // TODO: check with rootBinder.
}
