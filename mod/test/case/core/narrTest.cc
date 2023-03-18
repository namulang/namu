#include "../../namuTest.hpp"
#include <chrono>

using namespace namu;
using namespace std;

struct narrTest : public namuTest {};

namespace {
    class myNode : public node {
        NAMU(CLASS(myNode, node))

    public:
        myNode(int num): number(num) {}

        nbicontainer& subs() override { return nulOf<nbicontainer>(); }
        nbool canRun(const args& types) const override { return false; }
        str run(const args& a) override { return str(); }

        int number;
    };

    void benchMarkNArr(int cnt) {
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

        NAMU_I("[benchMarkNArr]: vector took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);

        narr arr;
        start = chrono::steady_clock::now();
        for(int n=0; n < cnt; n++) {
            arr.add(*(new myNode(n)));
        }
        sz = arr.len();
        startDeleting = chrono::steady_clock::now();
        arr.rel();
        end = chrono::steady_clock::now();

        addingElapsed = startDeleting - start;
        removingElapsed = end - startDeleting;
        totalElapsed = end - start;

        NAMU_I("[benchMarkNArr]: narr took total %d ms for adding(%dms) & removing(%dms) of %d elems.", totalElapsed / chrono::milliseconds(1), addingElapsed / chrono::milliseconds(1), removingElapsed / chrono::milliseconds(1), sz);
    }

    class myMyNode : public myNode {
        NAMU(CLASS(myMyNode, myNode))

    public:
        myMyNode(int num): super(num) {}
    };
}

TEST_F(narrTest, instantiateTest) {
    narr arr;
}

TEST_F(narrTest, shouldNotCanAddLocalObject) {
    tnarr<myNode> arr;
    ASSERT_EQ(arr.len(), 0);

    {
        myNode localObj(5);
        ASSERT_TRUE(arr.add(localObj));
        ASSERT_FALSE(nul(arr[0]));
        ASSERT_EQ(arr.len(), 1);
    }

    ASSERT_EQ(arr.len(), 1);
    auto& elem = arr[0];
    ASSERT_TRUE(nul(elem));
}

TEST_F(narrTest, simpleAddDelTest) {
    tnarr<myNode> arr;
    ASSERT_EQ(arr.len(), 0);

    const int EXPECT_NUMBER = 5;
    arr.add(*(new myNode(EXPECT_NUMBER)));
    ASSERT_EQ(arr.len(), 1);

    auto elem1 = arr[0].cast<myNode>();
    ASSERT_FALSE(nul(elem1));
    ASSERT_EQ(elem1.number, EXPECT_NUMBER);
}

TEST_F(narrTest, addDel10Elems) {
    tnarr<myNode> arr;
    const int cnt = 10;
    for(int n=0; n < cnt; n++) {
        ASSERT_TRUE(arr.add(*(new myNode(n))));
    }

    ASSERT_EQ(arr.len(), cnt);
}

TEST_F(narrTest, benchMarkNArrTest) {
    benchMarkNArr(100);
    benchMarkNArr(1000);
    benchMarkNArr(10000);
}

TEST_F(narrTest, testIter) {
    narr arr;
    arr.add(new myNode(0));
    arr.add(new myNode(1));
    arr.add(new myNode(2));

    auto e = arr.begin();
    auto head = e++;
    auto index2 = ++e;

    EXPECT_TRUE(arr.begin()+2 == index2);
    EXPECT_TRUE(arr.begin() == head);

    ASSERT_EQ(e.next(1), 0);
}

TEST_F(narrTest, testucontainableAPI) {
    //  initial state:
    tnarr<myNode>* arr = new tnarr<myNode>();
    tucontainable<myNode>* con = arr;
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
        myNode& elem = e->cast<myNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    // get & each:
    expectVal = 0;
    for(int n=0; n < arr->len() ;n++) {
        myNode& elem = arr->get(n).cast<myNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    {
        tnarr<myNode> tray = arr->getAll<myNode>([](const myNode& elem) {
            return true;
        });
        ASSERT_EQ(tray.len(), 2);

        int cnt = 0;
        tray = arr->getAll<myNode>([&cnt](const myNode& elem) {
            if(cnt++ >= 1) return false;
            return true;
        });
        ASSERT_EQ(tray.len(), 1);
    }

    myMyNode& tray = arr->get<myMyNode>([](const myMyNode& elem) {
        if(elem.number == 1) return true;
        return false;
    });
    ASSERT_FALSE(nul(tray));

    //  del:
    ASSERT_TRUE(con->del());
    ASSERT_EQ(con->len(), 1);
    ASSERT_EQ(arr->get(0).number, 0);

    //  add with element:
    tnarr<myNode> arr2;
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

    ASSERT_EQ(arr2[0].cast<myNode>().number, 0);
    ASSERT_EQ(arr2[1].cast<myNode>().number, 1);
    ASSERT_EQ(arr2[2].cast<myNode>().number, 6);
    ASSERT_EQ(arr2[3].cast<myNode>().number, 5);
    ASSERT_EQ(arr2[4].cast<myNode>().number, 2);
    ASSERT_EQ(arr2[5].cast<myNode>().number, 3);

    ASSERT_EQ(con->len(), 1);
    con->add(arr2.iterate(1), arr2.iterate(3));
    ASSERT_EQ(con->len(), 3);
    auto e2=arr->begin();
    myNode* elem = &e2.get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 0);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 1);

    elem = &(++e2)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    ASSERT_FALSE(++e2);

    ASSERT_TRUE(con->len() > 0);
    con->rel();
    ASSERT_TRUE(con->len() == 0);

    con->add(arr2.begin() + 2, arr2.end());
    ASSERT_EQ(con->len(), 4);
    e2 = arr->begin();
    elem = &e2.get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e2).get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 5);

    elem = &(++e2).get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 2);

    elem = &(++e2).get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    ASSERT_TRUE(con->del(con->begin() + 1, con->begin() + 3));
    ASSERT_EQ(con->len(), 2);
    e2 = arr->begin();
    elem = &e2.get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e2).get();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    delete con;
}

TEST_F(narrTest, testRangeBasedForLoop) {

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
