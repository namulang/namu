#include "../common/dep.hpp"

struct NoSuper {};
struct HasSuper : public NoSuper {
    typedef NoSuper Super;
};

#define WRD_TAG

namespace wrd { namespace meta {

    TEST(RttiTest, SuperTypedefTest) {
        ASSERT_FALSE(TIfHasSuperTypedef<NoSuper>::is);
        ASSERT_TRUE(TIfHasSuperTypedef<HasSuper>::is);
    }

    TEST(RttiTest, AdaptiveSuperTest) {
        ASSERT_EQ(TType<TAdaptiveSuper<NoSuper>::Super>(), TType<Adam>());
        WRD_I(typeid(TAdaptiveSuper<NoSuper>::Super).name())
    }
}}
