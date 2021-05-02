#include "../common/dep.hpp"
#include "../../src/builtin/container/native/ncontainer.inl"

using namespace wrd;
using namespace std;

class myNode : public node {
    WRD_CLASS(myNode, node)

public:
    myNode(int num): number(num) {}

    ncontainer& subs() override { return nulOf<ncontainer>(); }
    wbool canRun(const wtypes& types) const override { return false; }
    str run(ncontainer& args) override { return str(); }

    int number;
};

TEST(nchainTest, instantiateTest) {
    nchain chn;
    ASSERT_FALSE(nul(chn.getContainer()));
}

void simpleAddDelTest(int cnt) {
    tnarr<myNode>* arr = new tnarr<myNode>();
    nchain chn(*arr);
    ASSERT_EQ(0, arr->len());
    ASSERT_EQ(chn.len(), arr->len());
    ASSERT_TRUE(nul(chn.getNext()));

    vector<myNode*> tray;
    for(int n=0; n < cnt ;n++) {
        myNode* new1 = new myNode(n);
        arr->add(new1);
        tray.push_back(new1);
    }

    ASSERT_EQ(chn.len(), cnt);
    ASSERT_EQ(chn.len(), cnt);
    ASSERT_EQ(chn.len(), cnt);
    ASSERT_EQ(chn.len(), cnt);

    wbool isOk = false;
    int index = 0;
    ASSERT_TRUE(nul(chn.getNext()));
    chn.each<myNode>([&](const wrd::iterator& e, const myNode& elem) {
        if(&elem != tray[index]) return isOk = false;
        if(elem.number != index++) return isOk = false;
        return isOk = true;
    });
    ASSERT_TRUE(isOk);
}

TEST(nchainTest, simpleAddDelTest10) {
    simpleAddDelTest(10);
}
TEST(nchainTest, simpleAddDelTest1000) {
    simpleAddDelTest(1000);
}
TEST(nchainTest, simpleAddDelTest10000) {
    simpleAddDelTest(10000);
}

class myMyNode : public myNode {
    WRD_CLASS(myMyNode, myNode)

public:
    myMyNode(int num): super(num) {}
};
TEST(nchainTest, testcontainableAPI) {
    //  initial state:
    tstr<nchain> arr(new nchain());
    containable* con = &arr.get();
    ASSERT_EQ(con->len(), 0);

    wrd::iterator head = arr->begin();
    ASSERT_TRUE(head.isEnd());
    wrd::iterator tail = con->end();
    ASSERT_TRUE(tail.isEnd());

    ASSERT_TRUE(con->add(con->begin(), new myNode(0)));
    ASSERT_TRUE(con->add(con->end(), new myMyNode(1)));
    ASSERT_EQ(con->len(), 2);
    ASSERT_EQ(con->len(), 2);
    ASSERT_EQ(con->len(), 2);
    ASSERT_EQ(con->len(), 2);
    ASSERT_EQ(con->len(), 2);
    ASSERT_EQ(con->len(), 2);

    //  add:
    int expectVal = 0;
    for(wrd::iterator e=con->begin(); e != con->end() ;e++) {
        myNode& elem = e->cast<myNode>();
        ASSERT_FALSE(nul(elem));
        ASSERT_EQ(elem.number, expectVal++);
    }

    //  get & each:
    narr tray = arr->get<myNode>([](const myNode& elem) {
        return true;
    });
    ASSERT_EQ(tray.len(), 2);

    int cnt = 0;
    tray = arr->get<myNode>([&cnt](const myNode& elem) {
        if(cnt >= 1) return false;
        cnt++;
        return true;
    });
    ASSERT_EQ(tray.len(), 1);

    tray = arr->get<myMyNode>([](const myMyNode& elem) {
        if(elem.number == 1) return true;
        return false;
    });
    ASSERT_EQ(tray.len(), 1);

    //  del:
    ASSERT_TRUE(con->del());
    ASSERT_EQ(con->len(), 1);
    ASSERT_EQ(con->begin()->cast<myNode>().number, 0);

    //  add with element:
    narr arr2;
    ASSERT_EQ(arr2.add(*con), 1);
    ASSERT_TRUE(arr2.add(new myNode(1)));
    ASSERT_TRUE(arr2.add(new myMyNode(2)));
    ASSERT_TRUE(arr2.add(new myNode(3)));
    ASSERT_EQ(arr2[2].cast<myNode>().number, 2);
    ASSERT_EQ(arr2[3].cast<myNode>().number, 3);
    ASSERT_EQ(arr2.len(), 4);

    wrd::iterator e = arr2.begin();
    e = e + 2;
    ASSERT_EQ(e->cast<myNode>().number, 2);
    ASSERT_TRUE(arr2.add(e, new myNode(5)));
    ASSERT_TRUE(arr2.add(2, new myNode(6)));

    ASSERT_EQ(arr2[0].cast<myNode>().number, 0);
    ASSERT_EQ(arr2[1].cast<myNode>().number, 1);
    ASSERT_EQ(arr2[2].cast<myNode>().number, 6);
    ASSERT_EQ(arr2[3].cast<myNode>().number, 5);
    ASSERT_EQ(arr2[4].cast<myNode>().number, 2);
    ASSERT_EQ(arr2[5].cast<myNode>().number, 3);

    ASSERT_EQ(con->len(), 1);
    ASSERT_EQ(con->add(arr2.iter(1), arr2.iter(3)), 2);
    ASSERT_EQ(con->len(), 3);
    e=con->begin();
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
    con->empty();
    ASSERT_TRUE(con->len() == 0);

    ASSERT_EQ(con->add(arr2.iter(2), arr2.end()), 4);
    e = con->begin();
    elem = &e->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 5);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 2);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);

    ASSERT_EQ(con->del(con->begin() + 1, con->begin() + 3), 2);
    e = con->begin();
    elem = &e->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 6);

    elem = &(++e)->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, 3);
}

void examineChain2Element(nchain& chn, int val1, int val2) {
    myNode* elem = &chn.begin()->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, val1);

    elem = &(++chn.begin())->cast<myNode>();
    ASSERT_FALSE(nul(elem));
    ASSERT_EQ(elem->number, val2);
}

TEST(nchainTest, testLinkedChainWithOnly1Element) {
    narr arr1;
    arr1.add(new myNode(0));
    nchain chn1(arr1);
    ASSERT_EQ(chn1.len(), 1);

    narr arr2;
    arr2.add(new myNode(0));
    nchain chn2(arr2);
    ASSERT_EQ(chn2.len(), 1);
    chn2.link(chn1);
    ASSERT_EQ(chn2.len(), 2);

    int n=0;
    for(wrd::iterator e=chn2.begin(); e ;e++)
        n++;
    ASSERT_EQ(n, 2);
}

TEST(nchainTest, testLinkedChainWithNContainerAPI) {
    narr arr1;
    nchain chn1(arr1);
    narr arr2;
    nchain chn2(arr2);
    vector<int> expectElementNums;

    // add each chains:
    ASSERT_TRUE(chn2.add(new myNode(6)));
    ASSERT_TRUE(chn2.add(new myMyNode(5)));
    examineChain2Element(chn2, 6, 5);

    narr arr3;
    nchain chn3(arr3);
    ASSERT_TRUE(chn3.add(new myNode(2)));
    ASSERT_TRUE(chn3.add(new myMyNode(3)));
    examineChain2Element(chn3, 2, 3);

    ASSERT_TRUE(arr1.add(new myNode(0)));
    ASSERT_TRUE(chn1.add(new myMyNode(1)));
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
    ASSERT_EQ(chn1.len(), 6);

    // add with link:
    wrd::iterator e = chn1.begin();
    myNode* mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 0);

    mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 1);

    mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 6);

    mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 5);

    mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 2);

    mynode = &(e++)->cast<myNode>();
    ASSERT_FALSE(nul(mynode));
    ASSERT_EQ(mynode->number, 3);

    // each with link:
    int cnt = 0;
    auto lambda = [&cnt, &expectElementNums](const wrd::iterator& e, const myNode& elem) {
        if(nul(elem)) return cnt = -1, false;

        if(elem.number != expectElementNums[cnt++]) return cnt = -1, false;
        return true;
    };
    chn1.each<myNode>(lambda);
    ASSERT_EQ(cnt, 6);

    cnt = 2;
    chn2.each<myNode>(lambda);
    ASSERT_EQ(cnt, 6);

    cnt = 4;
    expectElementNums[5] = -1;
    chn3.each<myNode>(lambda);
    ASSERT_EQ(cnt, -1);

    // del with link:
    ASSERT_EQ(chn1.len(), 6);
    ASSERT_EQ(chn1.getContainer().len(), 2);
    ASSERT_EQ(chn2.len(), 4);
    ASSERT_EQ(chn2.getContainer().len(), 2);
    ASSERT_EQ(chn3.len(), 2);
    ASSERT_EQ(chn3.getContainer().len(), 2);

    ASSERT_EQ(chn1.del(chn1.begin()+1, chn2.begin()+1), 2);
    ASSERT_EQ(chn1.len(), 4);
    ASSERT_EQ(chn2.len(), 3);
}

TEST(nchainTest, testIfnchainLinkItself) {
    nchain chn;
    chn.add(new myNode(0));
    chn.add(new myNode(1));
    ASSERT_FALSE(chn.link(chn));
    ASSERT_EQ(chn.len(), 2);
}

TEST(nchainTest, testShouldLinkOverwritePrevious) {
    tstr<narr> arr1Str(new narr());
    const bindTag* arr1tag = &bindTag::getBindTag(arr1Str.getItsId());
    ASSERT_FALSE(nul(arr1tag));
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);

    tweak<narr> arr1Weak = arr1Str;
    arr1Str->add(new myNode(0));
    arr1Str->add(new myNode(1));
    ASSERT_EQ(arr1Str->len(), 2);
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);


    nchain chn2;
    chn2.add(new myNode(2));
    chn2.add(new myNode(3));
    ASSERT_EQ(chn2.len(), 2);

    ASSERT_TRUE(chn2.link(*arr1Str));
    ASSERT_EQ(arr1tag->getStrongCnt(), 2);
    // chn2 --> unknown chain instance holding arr1
    ASSERT_EQ(chn2.len(), 4);

    arr1Str.unbind();
    ASSERT_EQ(arr1tag->getStrongCnt(), 1);
    ASSERT_EQ(chn2.len(), 4);
    ASSERT_TRUE(arr1Weak.isBind());

    narr arr2;
    ASSERT_TRUE(arr1Weak.isBind());
    chn2.link(arr2);
    ASSERT_EQ(arr1tag->getStrongCnt(), 0);
    // this overwrites chain containing arr1. it's now dangling.
    // chn2(2, 3) --> unknown chain instance holding arr2(null)
    //   |--- X --> unknown chain instance holding arr1(0, 1)
    ASSERT_FALSE(arr1Weak.isBind());

    ASSERT_EQ(chn2.len(), 2);
}

TEST(nchainTest, testDelWithLink) {
    nchain chn;
    chn.add(new myNode(1));
    ASSERT_EQ(chn.len(), 1);

    {
        narr arr1;
        arr1.add(new myNode(2));
        arr1.add(new myNode(3));

        auto arr1Str = chn.link(arr1);
        // chn --> arr1Str with arr1
        //  ^
        //  |
        // head
        ASSERT_EQ(chn.len(), 3);
        tweak<nchain> arr2Weak;
        {
            narr arr2;
            arr2.add(new myNode(4));
            arr2.add(new myNode(5));
            arr2.add(new myNode(6));
            auto arr2Str = arr1Str->link(arr2);
            arr2Weak = arr2Str;
            // now, chn --> arr1Str with arr1 --> arr2Str with arr2
            ASSERT_EQ(arr2Str->len(), 3);
            ASSERT_EQ(arr1Str->len(), 3 + arr1.len());
            ASSERT_EQ(chn.len(), 1 + arr1.len() + arr2.len());
        }

        arr1Str->unlink();
        // now, chn --> arr1Str with arr1
        ASSERT_FALSE(arr2Weak.isBind());
        ASSERT_EQ(chn.len(), 1 + arr1.len());

        myNode& last = chn.iter(chn.len() - 1)->cast<myNode>();
        ASSERT_EQ(last.number, 3);
    }
    chn.unlink();
    ASSERT_EQ(chn.len(), 1);
}

TEST(nchainTest, testLastIterator) {
    nchain chn;
    ASSERT_EQ(chn.len(), 0);
    chn.add(new myNode(1));
    chn.add(new myNode(3));
    chn.add(chn.last(), new myNode(2));

    wint checker = 0;
    wbool sorted = true;
    chn.each<myNode>([&](const wrd::iterator& e, const myNode& elem) {
        return sorted = (elem.number == ++checker);
    });
    ASSERT_TRUE(sorted);
}

TEST(nchainTest, testRangeBasedForLoop) {
    nchain arr1;
    arr1.add(new myNode(3));
    arr1.add(new myNode(7));
    nchain arr2;
    arr2.add(new myNode(1));
    arr2.add(new myNode(2));
    arr1.link(arr2);

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
    for(wrd::iterator e=arr1.begin(); e ; e++)
        expect += e->cast<myNode>().number;

    ASSERT_EQ(sum, expect);
}
