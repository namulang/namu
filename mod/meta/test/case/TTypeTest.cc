#include "../common/dep.hpp"

using namespace wrd;

TEST(TTypeTest, initSystem) {}

class MyClass {
    WRD_INIT_META(MyClass);
};

struct MyDerivedClass : public MyClass {
    WRD_INIT_META(MyDerivedClass);
    typedef MyClass Super;
};

TEST(TTypeTest, basicBehavior) {
    ASSERT_FALSE(TType<MyClass>().isTemplate());
    ASSERT_FALSE(TType<MyClass>().isAbstract());

    const Type& type = TType<MyClass>();
    EXPECT_STREQ(type.getName().c_str(), "MyClass");

    const Types& subs = type.getSubs();
    ASSERT_EQ(subs.size(), 1);
    ASSERT_EQ(*subs[0], TType<MyDerivedClass>::get());

    ASSERT_STREQ(type.getSuper().getName().c_str(), "wrd::Adam");
}

TEST(TTypeTest, CustomTypeInheritTest) {
    static const std::string trg = "injected";
    static const int fooRet = 22;

    struct A {};
    struct CustomA {
        typedef struct MyType : Type {
            int foo() const {
                return fooRet;
            }
            const std::string& getName() const {
                return trg;
            }
        } SuperType;
    };

    EXPECT_NE(TType<A>().getName(), TType<CustomA>().getName());
    EXPECT_EQ(TType<CustomA>::get().foo(), fooRet);
}


struct A {
    WRD_INIT_META(A);

    A(): value(true) {}
    wbool value;
};
TEST(TTypeTest, makeInstanceTest) {
    TType<A> type;
    A* arr[] = {(A*) type.make(), type.makeAs<A>()};
    ASSERT_TRUE(arr[0]);
    ASSERT_TRUE(arr[1]);
    ASSERT_NE(arr[0], arr[1]);
}

struct B {
    WRD_INIT_META(B);

    B(wbool newValue): value(newValue) {}
    wbool value;
};
TEST(TTypeTest, makeInstanceNegativeTest) {
    TType<B> type;
    ASSERT_FALSE(type.make());
}
