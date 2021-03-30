#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {
}

TEST(TRefFixture, testCast) {
    TRef<Obj> obj(new Obj());

    Obj& cast = *obj;
    ASSERT_FALSE(nul(cast));
}
