#include "../common/dep.hpp"

namespace wrd { namespace meta {

    TEST(DefaultBehavior, initSystem) {}

    class MyClass {
        WRD_INIT_META(MyClass);
    };

    struct MyDerivedClass : public MyClass {
        WRD_INIT_META(MyDerivedClass);
        typedef MyClass Super;
    };

    TEST(DefaultBehavior, basicBehavior) {
        ASSERT_FALSE(TType<MyClass>().isTemplate());
        ASSERT_FALSE(TType<MyClass>().isAbstract());

        const Type& type = TType<MyClass>();
        ASSERT_STREQ(type.getName().c_str(), "wrd::meta::MyClass");

        const Types& subs = type.getSubs();
        ASSERT_EQ(subs.size(), 1);
        ASSERT_EQ(*subs[0], TType<MyDerivedClass>::get());

        ASSERT_STREQ(type.getSuper().getName().c_str(), "wrd::meta::Adam");
    }

}}
