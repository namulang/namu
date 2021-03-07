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
