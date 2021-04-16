#include "../common/dep.hpp"
#include "../../src/container/native/NContainer.inl"
#include <chrono>

using namespace wrd;
using namespace std;

class MyNode : public Node {
    WRD_CLASS(MyNode, Node)

public:
    MyNode(int num): number(num) {}

    NContainer& subs() override { return nulOf<NContainer>(); }
    wbool canRun(const WTypes& types) const override { return false; }
    Str run(NContainer& args) override { return Str(); }

    int number;
};

TEST(NArrFixture, instantiateTest) {
    NArr arr;
}

TEST(NArrFixture, shouldNotCanAddLocalObject) {
    TNArr<MyNode> arr;
    ASSERT_EQ(arr.getLen(), 0);

    {
        MyNode localObj(5);
        ASSERT_TRUE(arr.add(localObj));
        ASSERT_FALSE(nul(arr[0]));
        ASSERT_EQ(arr.getLen(), 1);
    }

    ASSERT_EQ(arr.getLen(), 1);
    auto& elem = arr[0];
    ASSERT_TRUE(nul(elem));
}

TEST(NArrFixture, simpleAddDelTest) {
    TNArr<MyNode> arr;
    ASSERT_EQ(arr.getLen(), 0);

    const int EXPECT_NUMBER = 5;
    arr.add(*(new MyNode(EXPECT_NUMBER)));
    ASSERT_EQ(arr.getLen(), 1);

    auto elem1 = arr[0].cast<MyNode>();
    ASSERT_FALSE(nul(elem1));
    ASSERT_EQ(elem1.number, EXPECT_NUMBER);
}

TEST(NArrFixture, addDel10Elems) {
    TNArr<MyNode> arr;
    const int cnt = 10;
    for(int n=0; n < cnt; n++) {
        ASSERT_TRUE(arr.add(*(new MyNode(n))));
    }

    ASSERT_EQ(arr.getLen(), cnt);
}

void benchMarkNArr(int cnt) {
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
    WRD_I("[benchMarkNArr]: vector took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
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
    WRD_I("[benchMarkNArr]: NArr took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
}

TEST(NArrFixture, benchMarkNArrTest) {
    benchMarkNArr(100);
    benchMarkNArr(1000);
    benchMarkNArr(10000);
}

class MyMyNode : public MyNode {
    WRD_CLASS(MyMyNode, MyNode)

public:
    MyMyNode(int num): super(num) {}
};

TEST(NArrFixture, testIter) {
    NArr arr;
    arr.add(new MyNode(0));
    arr.add(new MyNode(1));
    arr.add(new MyNode(2));

    typedef NArr::NArrIteration NArrIteration;

    Iter e = arr.head();
    Iter head = e++;
    Iter index2 = ++e;

    EXPECT_TRUE(arr.head()+2 == index2);
    EXPECT_TRUE(arr.head() == head);

    ASSERT_EQ(e.next(1), 0);
}

TEST(NArrFixture, testContainableAPI) {
    //  initial state:
    TNArr<MyNode>* arr = new TNArr<MyNode>();
    Containable* con = arr;
    ASSERT_EQ(con->getLen(), 0);

    Iter head = con->head();
    ASSERT_TRUE(head.isEnd());
    Iter tail = con->tail();
    ASSERT_TRUE(tail.isEnd());

    ASSERT_TRUE(con->add(con->head(), new MyNode(0)));
    ASSERT_TRUE(con->add(con->tail(), new MyMyNode(1)));
    ASSERT_EQ(con->getLen(), 2);

    // add:
    int expectVal = 0;
    for(Iter e=con->head(); e != con->tail() ;e++) {
        MyNode& elem = e->cast<MyNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    // get & each:
    expectVal = 0;
    for(int n=0; n < arr->getLen() ;n++) {
        MyNode& elem = arr->get(n).cast<MyNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    NArr tray = arr->get<MyNode>([](const MyNode& elem) {
        return true;
    });
    ASSERT_EQ(tray.getLen(), 2);

    int cnt = 0;
    tray = arr->get<MyNode>([&cnt](const MyNode& elem) {
        if(cnt++ >= 1) return false;
        return true;
    });
    ASSERT_EQ(tray.getLen(), 1);

    tray = arr->get<MyMyNode>([](const MyMyNode& elem) {
        if(elem.number == 1) return true;
        return false;
    });
    ASSERT_EQ(tray.getLen(), 1);

    //  del:
    ASSERT_TRUE(con->del());
    ASSERT_EQ(con->getLen(), 1);
    ASSERT_EQ(arr->get(0).number, 0);

    //  add with element:
    TNArr<MyNode> arr2;
    ASSERT_EQ(arr2.add(*con), 1);
    ASSERT_TRUE(arr2.add(new MyNode(1)));
    ASSERT_TRUE(arr2.add(new MyMyNode(2)));
    ASSERT_TRUE(arr2.add(new MyNode(3)));
    ASSERT_EQ(arr2[2].number, 2);
    ASSERT_EQ(arr2[3].number, 3);
    ASSERT_EQ(arr2.getLen(), 4);

    TIter<MyNode> e = arr2.headT();
    e = e + 2;
    ASSERT_EQ(e->number, 2);
    ASSERT_TRUE(arr2.add(e, new MyNode(5)));
    ASSERT_TRUE(arr2.add(2, new MyNode(6)));

    ASSERT_EQ(arr2[0].cast<MyNode>().number, 0);
    ASSERT_EQ(arr2[1].cast<MyNode>().number, 1);
    ASSERT_EQ(arr2[2].cast<MyNode>().number, 6);
    ASSERT_EQ(arr2[3].cast<MyNode>().number, 5);
    ASSERT_EQ(arr2[4].cast<MyNode>().number, 2);
    ASSERT_EQ(arr2[5].cast<MyNode>().number, 3);

    ASSERT_EQ(con->getLen(), 1);
    ASSERT_EQ(con->add(arr2.iter(1), arr2.iter(3)), 2);
    ASSERT_EQ(con->getLen(), 3);
    e=arr->headT();
    MyNode* elem = &e->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 0);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 1);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    ASSERT_FALSE(++e);

    ASSERT_TRUE(con->getLen() > 0);
    con->empty();
    ASSERT_TRUE(con->getLen() == 0);

    ASSERT_EQ(con->add(arr2.head() + 2, arr2.tail()), 4);
    e = arr->headT();
    elem = &e->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 5);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 2);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    ASSERT_EQ(con->del(con->head() + 1, con->head() + 3), 2);
    e = arr->headT();
    elem = &e->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    delete con;
}
