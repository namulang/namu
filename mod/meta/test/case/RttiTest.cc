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

TEST(RttiTest, BasicBehavior) {
    ASSERT_FALSE(TIfHasSuperTypedef<NoSuper>::is);
    ASSERT_TRUE(TIfHasSuperTypedef<HasSuper>::is);

    ASSERT_EQ(TType<TAdaptiveSuper<NoSuper>::Super>(), TType<Adam>());
    ASSERT_EQ(TType<TAdaptiveSuper<HasSuper>::Super>(), TType<NoSuper>::get());

    ASSERT_FALSE((TIfSub<NoSuper, HasSuper>::is));
    ASSERT_TRUE((TIfSub<HasSuper, NoSuper>::is));

    void* instance = TInstanceMaker<NoSuper>::make();
    WRD_I("instance=%x", instance);
    ASSERT_FALSE(instance);
    instance = TInstanceMaker<HasSuper>::make();
    WRD_I("instance=%x", instance);
    ASSERT_TRUE(instance);

    ASSERT_FALSE(TIfHasSuperTypedef<NoSuper>::is);
    ASSERT_TRUE(TIfHasSuperTypedef<HasSuper>::is);

    ASSERT_EQ(typeid(TAdaptiveSuper<NoSuper>::Super), typeid(Adam));
    ASSERT_EQ(typeid(TAdaptiveSuper<HasSuper>::Super), typeid(NoSuper));
}

TEST(RttiTest, SuperTypeDefTest) {
    struct A {};
    struct CustomA {
        typedef struct MyType : Type {
            int foo() {
                return 22;
            }
        } SuperType;
    };

    ASSERT_EQ(typeid(TSuperTypeDef<A>::is), typeid(Type));
    ASSERT_EQ(typeid(TSuperTypeDef<CustomA>::is), typeid(CustomA::MyType));
}
