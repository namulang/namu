#include "../common/dep.hpp"

namespace wrd { namespace memlite {

    struct A : public Instance {
        int age;

        const Type& getType() const {
            return TType<A>::get();
        }
    };

    struct B : public A {
        float grade;

        const Type& getType() const {
            return TType<B>::get();
        }
    };

    TEST(WatcherTest, localVariableBindTagTest) {
        A a;
        const BindTag& tag = a.getBindTag();
        ASSERT_FALSE(nul(tag));
        ASSERT_TRUE(tag.getId().s.serial);

        const Chunk& chk = tag.getChunk();
        ASSERT_TRUE(nul(chk));
    }

    TEST(WatcherTest, heapVariableBindTagTest) {
        std::vector<A*> arr;

        for(int n=0; n < 10; n++)
        {
            A* new1 = new A();

            const BindTag& tag = new1->getBindTag();
            ASSERT_FALSE(nul(tag));
            ASSERT_GT(tag.getId().s.serial, 0);
            ASSERT_TRUE(tag.isBind());
            ASSERT_EQ(tag.getBindable(), TType<Instance>());
            ASSERT_TRUE(tag.canBind(TType<Instance>()));

            Id id = tag.getId();
            ASSERT_NE(id.s.tagN, WRD_INDEX_ERROR);
            ASSERT_NE(id.s.chkN, WRD_INDEX_ERROR);
            ASSERT_GT(id.s.serial, 0);
            ASSERT_TRUE(tag.isHeap());

            const Chunk& chk = tag.getChunk();
            ASSERT_FALSE(nul(chk));
            ASSERT_TRUE(chk.has(*new1));
            ASSERT_TRUE(chk.getEOB());
            ASSERT_TRUE(chk.getHeap());
            ASSERT_GT(chk.getLen(), 0);
            ASSERT_GT(chk.getSize(),  0);
            new1->age = n;
            arr.push_back(new1);
        }

        for(A* e : arr)
            delete e;
        arr.clear();
    }
}}
