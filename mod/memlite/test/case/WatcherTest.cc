#include "../common/dep.hpp"

using namespace std;
using namespace wrd;

struct A : public Instance {
    int age;

    const Type& getType() const override {
        return TType<A>::get();
    }
};

struct B : public A {
    float grade;

    const Type& getType() const override {
        return TType<B>::get();
    }
};

TEST(WatcherTest, localVariableBindTagTest) {
    A a;
    const BindTag& tag = a.getBindTag();
    ASSERT_FALSE(nul(tag));
    ASSERT_TRUE(tag.getId().serial);

    const Chunk& chk = tag.getChunk();
    ASSERT_TRUE(nul(chk));
}

TEST(WatcherTest, heapVariableBindTagTest) {
    vector<A*> arr;

    for(int n=0; n < 10; n++)
    {
        A* new1 = new A();

        const BindTag& tag = new1->getBindTag();
        ASSERT_FALSE(nul(tag));
        ASSERT_GT(tag.getId().serial, 0);
        ASSERT_TRUE(tag.isBind());
        ASSERT_EQ(tag.getBindable(), TType<Instance>());
        ASSERT_TRUE(tag.canBind(TType<Instance>()));

        Id id = tag.getId();
        ASSERT_NE(id.tagN, WRD_INDEX_ERROR);
        ASSERT_NE(id.chkN, WRD_INDEX_ERROR);
        ASSERT_GT(id.serial, 0);
        ASSERT_TRUE(tag.isHeap());

        const Chunk& chk = tag.getChunk();
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
    vector<Id> ids;

    for(int n=0; n < cnt ;n++) {
        A* new1 = new B();
        tray.push_back(new1);

        Id newId = new1->getId();
        ASSERT_EQ(newId, new1->getBindTag().getId());
        ids.push_back(newId);
    }

    for(int n=0; n < cnt; n++) {
        ASSERT_EQ(tray[n]->getId(), ids[n]);
    }
}

TEST(WatcherTest, addIntegrityTest100) {
    addIntegrityTest(100);
}

TEST(WatcherTest, addIntegrityTest10000) {
    addIntegrityTest(1000);
}

void addRemoveIntegrityTest(int cnt) {
    vector<A*> tray;
    vector<Id> ids;

    for(int n=0; n < cnt ;n++) {
        A* new1 = new B();
        tray.push_back(new1);

        Id newId = new1->getId();
        ASSERT_EQ(newId, new1->getBindTag().getId());
        ids.push_back(newId);
    }

    for(int n=0; n < cnt; n++) {
        ASSERT_EQ(tray[n]->getId(), ids[n]);
    }

}

TEST(WatcherTest, addRemoveIntegrityTest100) {
    addRemoveIntegrityTest(100);
}
