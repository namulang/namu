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
