#include "../common/dep.hpp"

using namespace std;
using namespace wrd;

struct A : public instance {
    int age;

    const type& getType() const override {
        return ttype<A>::get();
    }
};

struct B : public A {
    float grade;

    const type& getType() const override {
        return ttype<B>::get();
    }
};

TEST(watcherTest, localVariableBindTagTest) {
    A a;
    const bindTag& tag = a.getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_TRUE(tag.getId().serial);

    const chunk& chk = tag.getChunk();
    ASSERT_TRUE(nul(chk));
}

TEST(watcherTest, NestedClassBindTest) {
    class inner : public instance {
    public:
        const type& getType() const override {
            return ttype<inner>::get();
        }
    };

    class outer : public instance {
    public:
        outer(inner* in): inner(in) {}

        const type& getType() const override {
            return ttype<outer>::get();
        }

        inner* inner;
    };

    auto* b = new outer(new inner());
    ASSERT_TRUE(b->getId().isHeap());
    ASSERT_TRUE(b->inner->getId().isHeap());
}

TEST(watcherTest, heapVariableBindTagTest) {
    vector<A*> arr;

    for(int n=0; n < 10; n++)
    {
        A* new1 = new A();

        const bindTag& tag = new1->getBindTag();
        ASSERT_FALSE(nul(tag));
        ASSERT_GT(tag.getId().serial, 0);
        ASSERT_TRUE(tag.isBind());
        ASSERT_EQ(tag.getBindable(), ttype<instance>());
        ASSERT_TRUE(tag.canBind(ttype<instance>()));

        id i = tag.getId();
        ASSERT_NE(i.tagN, WRD_INDEX_ERROR);
        ASSERT_NE(i.chkN, WRD_INDEX_ERROR);
        ASSERT_GT(i.serial, 0);
        ASSERT_TRUE(i.isHeap());

        const chunk& chk = tag.getChunk();
        ASSERT_FALSE(nul(chk));
        ASSERT_TRUE(chk.has(*new1));
        ASSERT_GT(chk.getLen(), 0);
        ASSERT_GT(chk.getSize(),  0);
        new1->age = n;
        arr.push_back(new1);
    }

    for(A* e : arr)
        delete e;
    arr.clear();
}

void addIntegrityTest(int cnt) {
    vector<A*> tray;
    vector<id> ids;

    for(int n=0; n < cnt ;n++) {
        A* new1 = new B();
        tray.push_back(new1);

        id newId = new1->getId();
        ASSERT_EQ(newId, new1->getBindTag().getId());
        ids.push_back(newId);
    }

    for(int n=0; n < cnt; n++) {
        ASSERT_EQ(tray[n]->getId(), ids[n]);
    }
}

TEST(watcherTest, addIntegrityTest100) {
    addIntegrityTest(100);
}

TEST(watcherTest, addIntegrityTest10000) {
    addIntegrityTest(1000);
}

void addRemoveIntegrityTest(int cnt) {
    vector<A*> tray;
    vector<id> ids;

    for(int n=0; n < cnt ;n++) {
        A* new1 = new B();
        tray.push_back(new1);

        id newId = new1->getId();
        ASSERT_EQ(newId, new1->getBindTag().getId());
        ids.push_back(newId);
    }

    for(int n=0; n < cnt; n++) {
        ASSERT_EQ(tray[n]->getId(), ids[n]);
    }

}

TEST(watcherTest, addRemoveIntegrityTest100) {
    addRemoveIntegrityTest(100);
}
