#include "../common/dep.hpp"

using namespace wrd;

TEST(ttypeTest, initSystem) {}

class myClass {
    WRD_INIT_META(myClass);
};

struct myDerivedClass : public myClass {
    WRD_INIT_META(myDerivedClass);
    typedef myClass super;
};

TEST(ttypeTest, basicBehavior) {
    ASSERT_FALSE(ttype<myClass>().isTemplate());
    ASSERT_FALSE(ttype<myClass>().isAbstract());

    const type& type = ttype<myClass>();
    EXPECT_STREQ(type.getName().c_str(), "myClass");

    const types& subs = type.getSubs();
    ASSERT_EQ(subs.size(), 1);
    ASSERT_EQ(*subs[0], ttype<myDerivedClass>::get());

    ASSERT_STREQ(type.getSuper().getName().c_str(), "adam");
}

TEST(ttypeTest, customTypeInheritTest) {
    static const std::string trg = "injected";
    static const int fooRet = 22;

    struct A {};
    struct customA {
        typedef struct myType : type {
            int foo() const {
                return fooRet;
            }
            const std::string& getName() const {
                return trg;
            }
        } superType;
    };

    EXPECT_NE(ttype<A>().getName(), ttype<customA>().getName());
    EXPECT_EQ(ttype<customA>::get().foo(), fooRet);
}


struct A {
    WRD_INIT_META(A);

    A(): value(true) {}
    wbool value;
};
TEST(ttypeTest, makeInstanceTest) {
    ttype<A> type;
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
TEST(ttypeTest, makeInstanceNegativeTest) {
    ttype<B> type;
    ASSERT_FALSE(type.make());
}
