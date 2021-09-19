#include "../common/dep.hpp"

using namespace wrd;

namespace {
    struct myNode : public node {
        WRD(CLASS(myNode, node))

    public:
        myNode(int n): num(n) {}

        ncontainer& subs() override { return nulOf<ncontainer>(); }
        wbool canRun(const wtypes& types) const override { return false; }
        str run(const containable& args) override { return str(); }

        int num;
    };
}

struct frameTest : public ::testing::Test {

    stackFrame& getStackFrame() {
        return (stackFrame&) thread::get().getStackFrame();
    }

    void SetUp() {
        getStackFrame().add(new frame());
    }

    void TearDown() {
        thread::get().rel();
    }

    nchain& getLinks(frame& fr) {
        return *fr._links;
    }
};

TEST_F(frameTest, testAccessFrame) {
    getStackFrame().add(new frame);
}

TEST_F(frameTest, testFrameManipulateChainObjNegative) {
    frame& fr = getStackFrame().getCurrentFrame();

    nchain chnBase;
    chnBase.add(new myNode(1));
    chnBase.add(new myNode(2));
    fr.add(chnBase);

    nchain shares;
    shares.add(new myNode(3));
    nchain owns;
    owns.add(new myNode(4));
    owns.link(shares);
    ASSERT_EQ(owns.len(), 2);
    auto lambda = [](const myNode& elem) {
        return true;
    };
    ASSERT_FALSE(nul(owns.get<myNode>(lambda)));

    fr.add(*nchain::wrapDeep(owns));
    ASSERT_EQ(fr.subAll<myNode>(lambda).len(), 4);
    ASSERT_EQ(owns.getAll<myNode>(lambda).len(), 2);

    int expects[] = {4, 3, 1, 2};
    titer<myNode> e = getLinks(fr).begin<myNode>();
    for (int expect : expects) {
        ASSERT_EQ(expect, e->num);
        ++e;
    }
}
