#include "../common/dep.hpp"

struct NoSuper {
    virtual void abstract() = 0;
    static void staticMethod() {}
};
struct HasSuper : public NoSuper {
    typedef NoSuper Super;
    void abstract() {}
};

using namespace wrd;
using namespace wrd::meta;

TEST(RttiTest, BasicBehavior) {
    ASSERT_FALSE(TIfHasSuperTypedef<NoSuper>::is);
    ASSERT_TRUE(TIfHasSuperTypedef<HasSuper>::is);

    ASSERT_EQ(TType<TAdaptiveSuper<NoSuper>::Super>(), TType<Adam>());
    ASSERT_EQ(TType<TAdaptiveSuper<HasSuper>::Super>(), TType<NoSuper>::get());

    ASSERT_TRUE(TIfAbstract<NoSuper>::is);
    ASSERT_FALSE(TIfAbstract<HasSuper>::is);

    ASSERT_FALSE((TIfSub<NoSuper, HasSuper>::is));
    ASSERT_TRUE((TIfSub<HasSuper, NoSuper>::is));

    void* instance = TInstanceMaker<NoSuper>::make();
    if (!instance)
        WRD_I("instance == null")
    ASSERT_FALSE(instance);
    instance = TInstanceMaker<HasSuper>::make();
    if (!instance)
        WRD_I("instance == null")
    ASSERT_TRUE(instance);
}
