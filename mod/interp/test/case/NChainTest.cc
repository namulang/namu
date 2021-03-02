#include "../common/dep.hpp"

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

TEST(NChainFixture, simpleAdd1ElemTest) {
    TNArr<MyNode>* arr = new TNArr<MyNode>();
    NChain chn(*arr);
    ASSERT_EQ(0, arr->getLen());
    ASSERT_EQ(chn.getLen(), arr->getLen());
    ASSERT_TRUE(nul(chn.getNext()));

    const int EXPECT_NUMBER = 5;
    MyNode& new1 = *(new MyNode(EXPECT_NUMBER));
    arr->add(new1);
    ASSERT_EQ(chn.getLen(), 1);

    wbool isOk = false;
    chn.each<MyNode>([&isOk, &new1](const Iter& e, const MyNode& elem) {
        if(&elem != &new1) return isOk = false;
        if(elem.number != EXPECT_NUMBER) return isOk = false;
        isOk = true;
        return true;
    });

    ASSERT_TRUE(isOk);
}

TEST(NChainFixture, simpleAddDelTest) {
    TNArr<MyNode>* arr = new TNArr<MyNode>();
    NChain chn(*arr);
    ASSERT_EQ(0, arr->getLen());
    ASSERT_EQ(chn.getLen(), arr->getLen());
    ASSERT_TRUE(nul(chn.getNext()));

    const int EXPECT_NUMBER = 5;
    MyNode& new1 = *(new MyNode(EXPECT_NUMBER));
    arr->add(new1);
    ASSERT_EQ(chn.getLen(), 1);

    wbool isOk = false;
    chn.each<MyNode>([&isOk, &new1](const Iter& e, const MyNode& elem) {
        if(&elem != &new1) return isOk = false;
        if(elem.number != EXPECT_NUMBER) return isOk = false;
        isOk = true;
        return true;
    });

    ASSERT_TRUE(isOk);
}
