#include "../common/dep.hpp"
#include "../../src/container/native/NContainer.inl"

using namespace wrd;

class MyNode : public Node {
    WRD_CLASS(MyNode, Node)

public:
    MyNode(int num): number(num) {}

    int number;
};

TEST(NChainFixture, instantiateTest) {
    NChain chn;
    ASSERT_FALSE(nul(chn.getContainer()));
}

void simpleAddDelTest(int cnt) {
    TNArr<MyNode>* arr = new TNArr<MyNode>();
    NChain chn(*arr);
    ASSERT_EQ(0, arr->getLen());
    ASSERT_EQ(chn.getLen(), arr->getLen());
    ASSERT_TRUE(nul(chn.getNext()));

    vector<MyNode*> tray;
    for(int n=0; n < cnt ;n++) {
        MyNode* new1 = new MyNode(n);
        arr->add(new1);
        tray.push_back(new1);
    }

    ASSERT_EQ(chn.getLen(), n);

    wbool isOk = false;
    int index = 0;
    ASSERT_TRUE(nul(chn.getNext()));
    chn.each<MyNode>([&isOk, &new1](const Iter& e, const MyNode& elem) {
        if(&elem != tray[index++]) return isOk = false;
        if(elem.number != index) return isOk = false;
        return isOk = true;
    });
    ASSERT_TRUE(isOk);
}

TEST(NChainFixture, simpleAddDelTest1) {
    simpleAddDelTest(100);
}
TEST(NChainFixture, simpleAddDelTest1) {
    simpleAddDelTest(1000);
}
TEST(NChainFixture, simpleAddDelTest1) {
    simpleAddDelTest(10000);
}

class MyMyNode : public MyNode {
    WRD_CLASS(MyMyNode, MyNode)

public:
    MyMyNode(int num): Super(num) {}
};
TEST(NChainFixture, testContainableAPI) {
    //  initial state:
    TStr<NChain> arr = new NChain();
    Containable* con = &arr.get();
    ASSERT_EQ(con->getLen(), 0);

    Iter head = arr->head();
    ASSERT_TRUE(head.isEnd());
    Iter tail = con->tail();
    ASSERT_TRUE(tail.isEnd());

    ASSERT_TRUE(con->add(con->head(), new MyNode(0)));
    ASSERT_TRUE(con->add(con->tail(), new MyMyNode(1)));
    ASSERT_EQ(con->getLen(), 2);

    //  add:
    int expectVal = 0;
    for(Iter e=con->head(); e != con->tail() ;e++) {
        MyNode& elem = e->cast<MyNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    //  get & each:
    NArr tray = arr->get<MyNode>([](const MyNode& elem) {
        return true;
    });
    ASSERT_EQ(tray.getLen(), 2);

    int cnt = 0;
    tray = arr->get<MyNode>([&cnt](const MyNode& elem) {
        if(cnt >= 1) return false;
        cnt++;
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
    ASSERT_EQ(con->head()->cast<MyNode>().number, 0);

    //  add with element:
    NArr arr2;
    ASSERT_EQ(arr2.add(*con), 1);
    ASSERT_TRUE(arr2.add(new MyNode(1)));
    ASSERT_TRUE(arr2.add(new MyMyNode(2)));
    ASSERT_TRUE(arr2.add(new MyNode(3)));
    ASSERT_EQ(arr2[2].cast<MyNode>().number, 2);
    ASSERT_EQ(arr2[3].cast<MyNode>().number, 3);
    ASSERT_EQ(arr2.getLen(), 4);

    Iter e = arr2.head();
    e = e + 2;
    ASSERT_EQ(e->cast<MyNode>().number, 2);
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
    e=con->head();
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
    e = con->head();
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
    e = con->head();
    elem = &e->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e)->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);
}
