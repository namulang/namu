#include "../common/dep.hpp"

using namespace wrd;

struct A : public Instance {
    A(): age(0) {}
    A(int newAge): age(newAge) {}

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
    ASSERT_TRUE(b1->isHeap());

    Id id = tag.getId();
    ASSERT_GT(id.serial, 0);
    ASSERT_GE(id.tagN,  0);
}

TEST(BindTest, shouldBindTagInaccessibleAfterInstanceTermination) {
    Id id;
    const Watcher& watcher = Instancer::get().getWatcher();
    const BindTag* tag;
    {
        B b1;
        id = b1.getId();
        tag = &watcher[id].blk;
        ASSERT_FALSE(nul(tag));
        ASSERT_EQ(id, tag->getId());
    }

    ASSERT_TRUE(nul(watcher[id]));
}

TEST(BindTest, supportLocalBindingTest) {
    TStr<B> bind;
    ASSERT_FALSE(bind);

    {
        B b;
        bind.bind(b);
        ASSERT_TRUE(bind);
        ASSERT_EQ(&(*bind), &b);
    }

    ASSERT_FALSE(bind);
    ASSERT_TRUE(nul(*bind));
}

TEST(BindTest, bindSameInstanceFewTimesTest) {
    ASSERT_EQ(B::get(), 0);

    {
        B b1;
        ASSERT_EQ(B::get(), 1);
        ASSERT_EQ(b1.getBindTag().getStrongCnt(), 0);

        TStr<B> bb1(b1),
                bb2(TStr<B>(new B(b1))),
                bb3;
        ASSERT_EQ(B::get(), 2);
        ASSERT_TRUE(bb1.isBind());
        ASSERT_FALSE(nul(bb1->getBindTag()));
        ASSERT_EQ(bb1->getBindTag().getStrongCnt(), 0);

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

TEST(BindTest, assignTest) {
    TStr<A> strA(new A());
    TStr<A> strA1;

    ASSERT_TRUE(strA.getItsId().isValid());
    ASSERT_TRUE(strA.getItsId().isValid());
    ASSERT_FALSE(strA1.getItsId().isValid());
    strA = strA1;
    ASSERT_FALSE(strA.getItsId().isValid());
}

void integrity(int cnt) {
    std::vector<TStr<A>> tray;
    std::vector<Id> ids;
    for(int n=0; n < cnt; n++) {
        A* new1 = new A(n);
        tray.push_back(TStr<A>(new1));
        ids.push_back(new1->getId());
    }

    const Watcher& watcher = Instancer::get().getWatcher();
    for(int n=0; n < cnt;n++) {
        Id id = ids[n];
        ASSERT_EQ(tray[n]->getId(), id);

        const BindTag& tag = watcher[id].blk;
        ASSERT_EQ(id, tag.getId());
    }
}

TEST(BindTest, bindMultiplTimesIntegrityTest) {
    integrity(10);
    integrity(100);
    integrity(1000);
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
