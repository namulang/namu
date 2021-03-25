#include "../common/dep.hpp"
#include "../../src/container/native/NContainer.inl"

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

    ASSERT_EQ(chn.getLen(), cnt);
    ASSERT_EQ(chn.getLen(), cnt);
    ASSERT_EQ(chn.getLen(), cnt);
    ASSERT_EQ(chn.getLen(), cnt);

    wbool isOk = false;
    int index = 0;
    ASSERT_TRUE(nul(chn.getNext()));
    chn.each<MyNode>([&](const Iter& e, const MyNode& elem) {
        if(&elem != tray[index]) return isOk = false;
        if(elem.number != index++) return isOk = false;
        return isOk = true;
    });
    ASSERT_TRUE(isOk);
}

TEST(NChainFixture, simpleAddDelTest10) {
    simpleAddDelTest(10);
}
TEST(NChainFixture, simpleAddDelTest1000) {
    simpleAddDelTest(1000);
}
TEST(NChainFixture, simpleAddDelTest10000) {
    simpleAddDelTest(10000);
}

class MyMyNode : public MyNode {
    WRD_CLASS(MyMyNode, MyNode)

public:
    MyMyNode(int num): Super(num) {}
};
TEST(NChainFixture, testContainableAPI) {
    //  initial state:
    TStr<NChain> arr(new NChain());
    Containable* con = &arr.get();
    ASSERT_EQ(con->getLen(), 0);

    Iter head = arr->head();
    ASSERT_TRUE(head.isEnd());
    Iter tail = con->tail();
    ASSERT_TRUE(tail.isEnd());

    ASSERT_TRUE(con->add(con->head(), new MyNode(0)));
    ASSERT_TRUE(con->add(con->tail(), new MyMyNode(1)));
    ASSERT_EQ(con->getLen(), 2);
    ASSERT_EQ(con->getLen(), 2);
    ASSERT_EQ(con->getLen(), 2);
    ASSERT_EQ(con->getLen(), 2);
    ASSERT_EQ(con->getLen(), 2);
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

    ASSERT_EQ(con->add(arr2.iter(2), arr2.tail()), 4);
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

void examineChain2Element(NChain& chn, int val1, int val2) {
    MyNode* elem = &chn.head()->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, val1);

    elem = &(++chn.head())->cast<MyNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, val2);
}

TEST(NChainFixture, testLinkedChainWithOnly1Element) {
    NArr arr1;
    arr1.add(new MyNode(0));
    NChain chn1(arr1);
    ASSERT_EQ(chn1.getLen(), 1);

    NArr arr2;
    arr2.add(new MyNode(0));
    NChain chn2(arr2);
    ASSERT_EQ(chn2.getLen(), 1);
    chn2.link(chn1);
    ASSERT_EQ(chn2.getLen(), 2);

    int n=0;
    for(Iter e=chn2.head(); e ;e++)
        n++;
    ASSERT_EQ(n, 2);
}

TEST(NChainFixture, testLinkedChainWithNContainerAPI) {
    NArr arr1;
    NChain chn1(arr1);
    NArr arr2;
    NChain chn2(arr2);
    vector<int> expectElementNums;

    // add each chains:
    ASSERT_TRUE(chn2.add(new MyNode(6)));
    ASSERT_TRUE(chn2.add(new MyMyNode(5)));
    examineChain2Element(chn2, 6, 5);

    NArr arr3;
    NChain chn3(arr3);
    ASSERT_TRUE(chn3.add(new MyNode(2)));
    ASSERT_TRUE(chn3.add(new MyMyNode(3)));
    examineChain2Element(chn3, 2, 3);

    ASSERT_TRUE(arr1.add(new MyNode(0)));
    ASSERT_TRUE(chn1.add(new MyMyNode(1)));
    examineChain2Element(chn1, 0, 1);

    expectElementNums.push_back(0);
    expectElementNums.push_back(1);
    expectElementNums.push_back(6);
    expectElementNums.push_back(5);
    expectElementNums.push_back(2);
    expectElementNums.push_back(3);

    // link:
    ASSERT_TRUE(nul(chn1.getNext()));
    ASSERT_TRUE(nul(chn2.getNext()));
    ASSERT_TRUE(nul(chn3.getNext()));
    ASSERT_TRUE(chn1.link(chn2));
    ASSERT_TRUE(nul(chn1.getNext().getNext()));
    ASSERT_TRUE(chn2.link(chn3));
    ASSERT_TRUE(nul(chn3.getNext()));
    ASSERT_TRUE(nul(chn1.getNext().getNext().getNext()));
    ASSERT_EQ(chn1.getLen(), 6);

    // add with link:
    Iter e = chn1.head();
    MyNode* mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 0);

    mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 1);

    mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 6);

    mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 5);

    mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 2);

    mynode = &(e++)->cast<MyNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 3);

    // each with link:
    int cnt = 0;
    auto lambda = [&cnt, &expectElementNums](const Iter& e, const MyNode& elem) {
        if(nul(elem)) return cnt = -1, false;

        if(elem.number != expectElementNums[cnt++]) return cnt = -1, false;
        return true;
    };
    chn1.each<MyNode>(lambda);
    ASSERT_EQ(cnt, 6);

    cnt = 2;
    chn2.each<MyNode>(lambda);
    ASSERT_EQ(cnt, 6);

    cnt = 4;
    expectElementNums[5] = -1;
    chn3.each<MyNode>(lambda);
    ASSERT_EQ(cnt, -1);

    // del with link:
    ASSERT_EQ(chn1.getLen(), 6);
    ASSERT_EQ(chn1.getContainer().getLen(), 2);
    ASSERT_EQ(chn2.getLen(), 4);
    ASSERT_EQ(chn2.getContainer().getLen(), 2);
    ASSERT_EQ(chn3.getLen(), 2);
    ASSERT_EQ(chn3.getContainer().getLen(), 2);

    ASSERT_EQ(chn1.del(chn1.head()+1, chn2.head()+1), 2);
    ASSERT_EQ(chn1.getLen(), 4);
    ASSERT_EQ(chn2.getLen(), 3);
}

TEST(NChainFixture, testIfNChainLinkItself) {
    NChain chn;
    chn.add(new MyNode(0));
    chn.add(new MyNode(1));
    ASSERT_FALSE(chn.link(chn));
    ASSERT_EQ(chn.getLen(), 2);
}

TEST(NChainFixture, testShouldLinkOverwritePrevious) {
    TStr<NArr> arr1Str(new NArr());
    const BindTag* arr1tag = &BindTag::getBindTag(arr1Str.getItsId());
    ASSERT_FALSE(nul(arr1tag));
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);

    TWeak<NArr> arr1Weak = arr1Str;
    arr1Str->add(new MyNode(0));
    arr1Str->add(new MyNode(1));
    ASSERT_EQ(arr1Str->getLen(), 2);
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);


    NChain chn2;
    chn2.add(new MyNode(2));
    chn2.add(new MyNode(3));
    ASSERT_EQ(chn2.getLen(), 2);

    ASSERT_TRUE(chn2.link(*arr1Str));
    ASSERT_EQ(arr1tag->getStrongCnt(), 2);
    // chn2 --> unknown chain instance holding arr1
    ASSERT_EQ(chn2.getLen(), 4);

    arr1Str.unbind();
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);
    ASSERT_EQ(chn2.getLen(), 4);
    ASSERT_TRUE(arr1Weak.isBind());

    NArr arr2;
    ASSERT_TRUE(arr1Weak.isBind());
    chn2.link(arr2);
    ASSERT_EQ(arr1tag->getStrongCnt(), 0);
    // this overwrites chain containing arr1. it's now dangling.
    // chn2(2, 3) --> unknown chain instance holding arr2(null)
    //   |--- X --> unknown chain instance holding arr1(0, 1)
    ASSERT_FALSE(arr1Weak.isBind());

    ASSERT_EQ(chn2.getLen(), 2);
}

TEST(NChainFixture, testDelWithLink) {
    NChain chn;
    chn.add(new MyNode(1));
    ASSERT_EQ(chn.getLen(), 1);

    {
        NArr arr1;
        arr1.add(new MyNode(2));
        arr1.add(new MyNode(3));

        auto arr1Str = chn.link(arr1);
        // chn --> arr1Str with arr1
        //  ^
        //  |
        // head
        ASSERT_EQ(chn.getLen(), 3);
        TWeak<NChain> arr2Weak;
        {
            NArr arr2;
            arr2.add(new MyNode(4));
            arr2.add(new MyNode(5));
            arr2.add(new MyNode(6));
            auto arr2Str = arr1Str->link(arr2);
            arr2Weak = arr2Str;
            // now, chn --> arr1Str with arr1 --> arr2Str with arr2
            ASSERT_EQ(arr2Str->getLen(), 3);
            ASSERT_EQ(arr1Str->getLen(), 3 + arr1.getLen());
            ASSERT_EQ(chn.getLen(), 1 + arr1.getLen() + arr2.getLen());
        }

        arr1Str->unlink();
        // now, chn --> arr1Str with arr1
        ASSERT_FALSE(arr2Weak.isBind());
        ASSERT_EQ(chn.getLen(), 1 + arr1.getLen());

        MyNode& last = chn.iter(chn.getLen() - 1)->cast<MyNode>();
        ASSERT_EQ(last.number, 3);
    }
    chn.unlink();
    ASSERT_EQ(chn.getLen(), 1);
}

TEST(NChainFixture, testLastIterator) {
    NChain chn;
    ASSERT_EQ(chn.getLen(), 0);
    chn.add(new MyNode(1));
    chn.add(new MyNode(3));
    chn.add(chn.last(), new MyNode(2));

    wint checker = 0;
    wbool sorted = true;
    chn.each<MyNode>([&](const Iter& e, const MyNode& elem) {
        return sorted = (elem.number == ++checker);
    });
    ASSERT_TRUE(sorted);
}
