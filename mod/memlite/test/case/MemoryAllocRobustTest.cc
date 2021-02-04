#include "../common/dep.hpp"
#include <ctime>

using namespace wrd;

struct A : public Instance {
    WRD_SINGLETON_GETTER(const Type& getType() const, TType<A>)

    int age;
};

struct B : public A {
    WRD_SINGLETON_GETTER(const Type& getType() const, TType<B>)

    float grade;
};

struct PInstance { Id _id; };
struct PNode : public PInstance {};
struct PObject : public PNode {};

struct PA : public PObject {
    WRD_SINGLETON_GETTER(const Type& getType() const, TType<PA>)

    int age;
};

struct PB : public PA {
    WRD_SINGLETON_GETTER(const Type& getType() const, TType<PB>)

    float grade;
};

time_t run1(int& crc, int n)
{
    PA* parr[100000] = {0, };
    time_t start = clock();
    crc = 0;
    for(int i=0; i < n ;i++) {
        parr[i] = new PB();
        crc += *(int*) parr[i];
    }
    for(int i=0; i < n ;i++)
        delete parr[i];
    return clock() - start;
}

time_t run2(int& crc, int n)
{
    crc = 0;
    A* arr[100000] = {0, };
    time_t start = clock();
    for(int i=0; i < n ;i++) {
        arr[i] = new B();
        crc += *(int*) arr[i];
    }
    for(int i=0; i < n ;i++)
        delete arr[i];
    return clock() - start;
}

#define SPRINT(n) \
WRD_W("%d times new/delete : %f ms elapsed. crc=%d", n, ((float) run1(crc, (n))) / CLOCKS_PER_SEC*1000.0f, crc); \
WRD_W("%d times mempool    : %f ms elapsed. crc=%d", n, ((float) run2(crc, (n))) / CLOCKS_PER_SEC*1000.0f, crc);

TEST(MemoryAllocRobustTest, sprint10) {
    int crc = 0;
    SPRINT(10)
}

TEST(MemoryAllocRobustTest, sprint100) {
    int crc = 0;
    SPRINT(100)
}

TEST(MemoryAllocRobustTest, sprint1000) {
    int crc = 0;
    SPRINT(1000)
}

TEST(MemoryAllocRobustTest, sprint10000) {
    int crc = 0;
    SPRINT(10000)
}

TEST(MemoryAllocRobustTest, sprint50000) {
    int crc = 0;
    SPRINT(50000)
}

TEST(MemoryAllocRobustTest, sprint100000) {
    int crc = 0;
    SPRINT(100000)
}
