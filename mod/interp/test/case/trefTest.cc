#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
}

TEST(trefFixture, testCast) {
    tref<obj> obj1(new obj());

    obj& cast = *obj1;
    ASSERT_FALSE(nul(cast));
}
