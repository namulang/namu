#include "../common/dep.hpp"

struct NoSuper {};
struct HasSuper : public NoSuper {
    typedef NoSuper Super;
};

namespace wrd { namespace meta {

    TEST(RttiTest, SuperTypedefTest) {
        ASSERT_FALSE(TIfHasSuperTypedef<NoSuper>::is);
        ASSERT_TRUE(TIfHasSuperTypedef<HasSuper>::is);
    }

    TEST(RttiTest, AdaptiveSuperTest) {
        ASSERT_EQ(TType<TAdaptiveSuper<NoSuper>::Super>(), TType<Adam>());
        ASSERT_EQ(TType<TAdaptiveSuper<HasSuper>::Super>(), TType<NoSuper>::get());
    }
}}
