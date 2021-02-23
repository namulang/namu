#include "../common/dep.hpp"
#include <chrono>

using namespace wrd;
using namespace std;

class MyNode : public Node {
    WRD_CLASS(MyNode, Node)

public:
    MyNode(int num): number(num) {}

    int number;
};

TEST(NArrFixture, instantiateTest) {
    NArr arr;
}

TEST(NArrFixture, shouldNotCanAddLocalObject) {
    NArr arr;
    MyNode localObj(5);
    ASSERT_EQ(arr.getLen(), 0);

    ASSERT_FALSE(arr.add(localObj));
    ASSERT_EQ(arr.getLen(), 0);

    auto& elem = arr[0];
    ASSERT_TRUE(nul(elem));
}

TEST(NArrFixture, simpleAddDelTest) {
    NArr arr;
    ASSERT_EQ(arr.getLen(), 0);

    const int EXPECT_NUMBER = 5;
    arr.add(*(new MyNode(EXPECT_NUMBER)));
    ASSERT_EQ(arr.getLen(), 1);

    auto elem1 = arr[0].cast<MyNode>();
    ASSERT_FALSE(nul(elem1));
    ASSERT_EQ(elem1.number, EXPECT_NUMBER);
}

TEST(NArrFixture, addDel10Elems) {
    NArr arr;
    const int cnt = 10;
    for(int n=0; n < cnt; n++) {
        ASSERT_TRUE(arr.add(*(new MyNode(n))));
    }

    ASSERT_EQ(arr.getLen(), cnt);
}

void benchMark(int cnt) {
    Logger::get().setEnable(false);
    vector<Str> vec;

    auto start = chrono::steady_clock::now();
    for(int n=0; n < cnt; n++) {
        vec.push_back(Str(new MyNode(n)));
    }
    int sz = vec.size();
    auto startDeleting = chrono::steady_clock::now();
    vec.clear();
    auto end = chrono::steady_clock::now();

    auto addingElapsed = startDeleting - start;
    auto removingElapsed = end - startDeleting;
    auto totalElapsed = end - start;

    Logger::get().setEnable(true);
    WRD_I("[benchMark]: vector took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
    Logger::get().setEnable(false);


    NArr arr;
    start = chrono::steady_clock::now();
    for(int n=0; n < cnt; n++) {
        arr.add(*(new MyNode(n)));
    }
    sz = arr.getLen();
    startDeleting = chrono::steady_clock::now();
    arr.empty();
    end = chrono::steady_clock::now();

    addingElapsed = startDeleting - start;
    removingElapsed = end - startDeleting;
    totalElapsed = end - start;

    Logger::get().setEnable(true);
    WRD_I("[benchMark]: NArr took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
}

TEST(NArrFixture, benchMarkTest) {
    benchMark(100);
    benchMark(1000);
    benchMark(10000);
    benchMark(50000);
}
