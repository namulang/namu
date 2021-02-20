#include "../common/dep.hpp"

using namespace wrd;

struct A : public Instance {
    int age;

    const Type& getType() const override {
        return TType<A>::get();
    }
};

struct B : public Instance {
    B() { ++get(); }
    B(const B&) { ++get(); }
    ~B() { --get(); }

    float grade;

    static wcnt& get() {
        static wcnt n = 0;
        return n;
    }

    const Type& getType() const override {
        return TType<B>::get();
    }
};

TEST(BindTest, defaultBehaviorTest) {
    TStr<A> b1 = new A();
    ASSERT_FALSE(nul(*b1));
    ASSERT_FALSE(nul(b1->getType()));

    const BindTag& tag = b1->getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_TRUE(tag.isHeap());

    Id id = tag.getId();
    ASSERT_GT(id.s.serial, 0);
    ASSERT_GE(id.s.tagN,  0);
}

TEST(BindTest, shouldNotBindLocalInstance) {
    TStr<A> binder;
    ASSERT_FALSE(binder.bind(A()));
    ASSERT_FALSE(binder.isBind());
}

TEST(BindTest, bindSameInstanceFewTimesTest) {
    ASSERT_EQ(B::get(), 0);

    {
        B localB1;
        ASSERT_EQ(B::get(), 1);
        ASSERT_EQ(localB1.getBindTag().getStrongCnt(), 0);

        TStr<B> bb1(localB1),
                bb2(TStr<B>(new B(localB1))),
                bb3;
        ASSERT_EQ(B::get(), 2);
        ASSERT_FALSE(bb1.isBind());

        ASSERT_TRUE(bb2.isBind());
        ASSERT_FALSE(nul(bb2->getBindTag()));
        ASSERT_EQ(bb2->getBindTag().getStrongCnt(), 1);

        ASSERT_FALSE(bb3.isBind());
        bb3 = bb2;
        ASSERT_EQ(B::get(), 2);
        ASSERT_TRUE(bb3.isBind());
        ASSERT_FALSE(nul(bb3->getBindTag()));
        ASSERT_EQ(bb3->getBindTag().getStrongCnt(), 2);
        ASSERT_TRUE(bb2.unbind());
        ASSERT_FALSE(bb2.isBind());
        ASSERT_TRUE(nul(bb2.get()));
        ASSERT_EQ(bb3->getBindTag().getStrongCnt(), 1);
        ASSERT_EQ(B::get(), 2);
        ASSERT_TRUE(bb3.unbind());
        ASSERT_TRUE(bb1.unbind());
    }

    ASSERT_EQ(B::get(), 0);
}

TEST(BindTest, StrongAndWeakTest) {
    TStr<A> strA(new A());
    ASSERT_TRUE(strA.isBind());

    const BindTag& tag = strA->getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_EQ(tag.getStrongCnt(), 1);

    TWeak<A> weakA(*strA);
    const BindTag& tagWeak = weakA->getBindTag();
    ASSERT_FALSE(nul(tagWeak));
    ASSERT_EQ(&tagWeak, &tag);
    ASSERT_EQ(tagWeak.getStrongCnt(), 1);
}

TEST(BindTest, BindByValueTest) {
    TStr<A> strA(new A());
    const BindTag& tag = strA->getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_EQ(tag.getStrongCnt(), 1);

    Bind bindA(strA);
    ASSERT_EQ(&strA.get(), &bindA.get());
    ASSERT_EQ(tag.getStrongCnt(), 2);

    strA.unbind();
    ASSERT_EQ(tag.getStrongCnt(), 1);

    {
        Bind bindA2(bindA);
        ASSERT_EQ(tag.getStrongCnt(), 2);
    }

    ASSERT_EQ(tag.getStrongCnt(), 1);
    bindA.unbind();

    ASSERT_EQ(tag.getStrongCnt(), 0);
}

TEST(BindTest, WeakBindButInstanceGoneTest) {
    TStr<A> strA(new A());
    TWeak<A> weakA(*strA);

    const BindTag& tag = weakA->getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_EQ(tag.getStrongCnt(), 1);

    strA.unbind();
    ASSERT_FALSE(weakA.isBind());
    ASSERT_TRUE(nul(*weakA));
}
