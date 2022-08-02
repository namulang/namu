#include "../../namuTest.hpp"
#include <chrono>

using namespace namu;
using namespace std;

struct arrTest : public namuTest {};

namespace {
    class myNode : public node {
        WRD(CLASS(myNode, node))

    public:
        myNode(int num): number(num) {}

        nbicontainer& subs() override { return nulOf<nbicontainer>(); }
        wbool canRun(const ucontainable& types) const override { return false; }
        using super::run;
        str run(const ucontainable& args) override { return str(); }

        int number;
    };

    class myMyNode : public myNode {
        WRD(CLASS(myMyNode, myNode))

    public:
        myMyNode(int num): super(num) {}
    };

    void benchMarkArr(int cnt) {
        logger::get().setEnable(false);
        vector<str> vec;

        auto start = chrono::steady_clock::now();
        for(int n=0; n < cnt; n++) {

            vec.push_back(str(new myNode(n)));
        }
        int sz = vec.size();
        auto startDeleting = chrono::steady_clock::now();
        vec.clear();
        auto end = chrono::steady_clock::now();

        auto addingElapsed = startDeleting - start;
        auto removingElapsed = end - startDeleting;
        auto totalElapsed = end - start;

        logger::get().setEnable(true);
        WRD_I("[benchMarkArr]: vector took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
        logger::get().setEnable(false);


        arr arr1;
        start = chrono::steady_clock::now();
        for(int n=0; n < cnt; n++) {
            arr1.add(*(new myNode(n)));
        }
        sz = arr1.len();
        startDeleting = chrono::steady_clock::now();
        arr1.rel();
        end = chrono::steady_clock::now();

        addingElapsed = startDeleting - start;
        removingElapsed = end - startDeleting;
        totalElapsed = end - start;

        logger::get().setEnable(true);
        WRD_I("[benchMarkArr]: arr took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
    }
}

TEST_F(arrTest, instantiateTest) {
    arr arr1;
}

TEST_F(arrTest, shouldNotCanAddLocalObject) {
    tarr<myNode> arr1;
    ASSERT_EQ(arr1.len(), 0);

    {
        myNode localObj(5);
        ASSERT_TRUE(arr1.add(localObj));
        ASSERT_FALSE(nul(arr1[0]));
        ASSERT_EQ(arr1.len(), 1);
    }

    ASSERT_EQ(arr1.len(), 1);
    auto& elem = arr1[0];
    ASSERT_TRUE(nul(elem));
}

TEST_F(arrTest, simpleAddDelTest) {
    tarr<myNode> arr1;
    ASSERT_EQ(arr1.len(), 0);

    const int EXPECT_NUMBER = 5;
    arr1.add(*(new myNode(EXPECT_NUMBER)));
    ASSERT_EQ(arr1.len(), 1);

    auto elem1 = arr1[0].cast<myNode>();
    ASSERT_FALSE(nul(elem1));
    ASSERT_EQ(elem1.number, EXPECT_NUMBER);
}

TEST_F(arrTest, addDel10Elems) {
    tarr<myNode> arr1;
    const int cnt = 10;
    for(int n=0; n < cnt; n++) {
        ASSERT_TRUE(arr1.add(*(new myNode(n))));
    }

    ASSERT_EQ(arr1.len(), cnt);
}

TEST_F(arrTest, benchMarkArrTest) {
    benchMarkArr(100);
    benchMarkArr(1000);
    benchMarkArr(10000);
}

TEST_F(arrTest, testIter) {
    arr arr1;
    arr1.add(new myNode(0));
    arr1.add(new myNode(1));
    arr1.add(new myNode(2));

    auto e = arr1.begin();
    auto head = e++;
    auto index2 = ++e;

    EXPECT_TRUE(arr1.begin()+2 == index2);
    EXPECT_TRUE(arr1.begin() == head);

    ASSERT_EQ(e.next(1), 0);
}

TEST_F(arrTest, testContainableAPI) {
    //  initial state:
    tarr<myNode>* arr1 = new tarr<myNode>();
    tucontainable<myNode>* con = arr1;
    ASSERT_EQ(con->len(), 0);

    auto head = con->begin();
    ASSERT_TRUE(head.isEnd());
    auto tail = con->end();
    ASSERT_TRUE(tail.isEnd());

    ASSERT_TRUE(con->add(con->begin(), new myNode(0)));
    ASSERT_TRUE(con->add(con->end(), new myMyNode(1)));
    ASSERT_EQ(con->len(), 2);

    // add:
    int expectVal = 0;
    for(auto e=con->begin(); e != con->end() ;e++) {
        myNode& elem = *e;
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    // get & each:
    expectVal = 0;
    for(int n=0; n < arr1->len() ;n++) {
        myNode& elem = arr1->get(n).cast<myNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    {
        tnarr<myNode> tray = arr1->getAll<myNode>([](const myNode& elem) {
            return true;
        });
        ASSERT_EQ(tray.len(), 2);

        int cnt = 0;
        tray = arr1->getAll<myNode>([&cnt](const myNode& elem) {
            if(cnt++ >= 1) return false;
            return true;
        });
        ASSERT_EQ(tray.len(), 1);
    }

    myMyNode& tray = arr1->get<myMyNode>([](const myMyNode& elem) {
        if(elem.number == 1) return true;
        return false;
    });
    ASSERT_FALSE(nul(tray));

    //  del:
    ASSERT_TRUE(con->del());
    ASSERT_EQ(con->len(), 1);
    ASSERT_EQ(arr1->get(0).number, 0);

    //  add with element:
    tarr<myNode> arr2;
    arr2.add(*con);
    ASSERT_TRUE(arr2.add(new myNode(1)));
    ASSERT_TRUE(arr2.add(new myMyNode(2)));
    ASSERT_TRUE(arr2.add(new myNode(3)));
    ASSERT_EQ(arr2[2].number, 2);
    ASSERT_EQ(arr2[3].number, 3);
    ASSERT_EQ(arr2.len(), 4);

    auto e = arr2.begin();
    e = e + 2;
    ASSERT_EQ(e.get<myNode>().number, 2);
    ASSERT_TRUE(arr2.add(e, new myNode(5)));
    ASSERT_TRUE(arr2.add(2, new myNode(6)));

    ASSERT_EQ(arr2[0].number, 0);
    ASSERT_EQ(arr2[1].cast<myNode>().number, 1);
    ASSERT_EQ(arr2[2].number, 6);
    ASSERT_EQ(arr2[3].cast<myNode>().number, 5);
    ASSERT_EQ(arr2[4].number, 2);
    ASSERT_EQ(arr2[5].number, 3);

    ASSERT_EQ(con->len(), 1);
    tucontainable<myNode>::iter e11 = arr2.iterate(1),
                                e12 = arr2.iterate(3);
    con->add(e11, e12);
    ASSERT_EQ(con->len(), 3);
    e=arr1->begin();
    myNode* elem = &e->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 0);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 1);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    ASSERT_FALSE(++e);

    ASSERT_TRUE(con->len() > 0);
    con->rel();
    ASSERT_TRUE(con->len() == 0);

    con->add(arr2.begin() + 2, arr2.end());
    auto e2 = arr1->begin();
    elem = &e2.get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 5);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 2);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    ASSERT_TRUE(con->del(con->begin() + 1, con->begin() + 3));
    ASSERT_EQ(con->len(), 2);

    e2 = arr1->begin();
    elem = &e2->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    delete con;
}

TEST_F(arrTest, testDeepClone) {
    narr arr1;
    arr1.add(new myNode(1));
    arr1.add(new myNode(2));
    ASSERT_EQ(arr1.len(), 2);

    tstr<narr> arr2wrap = arr1.deepClone();
    ASSERT_TRUE(arr2wrap);
    narr& arr2 = *arr2wrap;
    ASSERT_EQ(arr1.len(), arr2.len());

    for(int n=0; n < 2; n++) {
        ASSERT_EQ(arr1[n].cast<myNode>().number, arr2[n].cast<myNode>().number);
        ASSERT_NE(&arr1[n], &arr2[n]);
    }
}

TEST_F(arrTest, testRangeBasedForLoop) {

    narr arr1;
    arr1.add(new myNode(3));
    arr1.add(new myNode(7));

    int sum = 0;
    for(auto& e : arr1) {
        myNode& cast = e.cast<myNode>();
        sum += cast.number;
    }

    int sum2 = 0;
    for(const node& e : arr1) {
        const myNode& cast = e.cast<myNode>();
        sum2 += cast.number;
    }
    ASSERT_EQ(sum2, sum);

    int expect = 0;
    for(int n=0; n < arr1.len(); n++)
        expect += arr1[n].cast<myNode>().number;

    ASSERT_EQ(sum, expect);
}
