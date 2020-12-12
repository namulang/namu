#include "../common/dep.hpp"

namespace wrd { namespace meta {

    TEST(DefaultBehavior, initSystem) {}

    class MyClass {};
    WRD_INIT_META(MyClass);

    TEST(DefaultBehavior, initMetaOfEmptyClass) {
    }

}}
