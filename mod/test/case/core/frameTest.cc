#include "../../namuTest.hpp"

using namespace namu;

namespace {
    struct myNode : public node {
        NAMU(CLASS(myNode, node))

    public:
        myNode(int n): num(n) {}

        nbicontainer& subs() override { return nulOf<nbicontainer>(); }
        priority prioritize(const args& a) const override { return NO_MATCH; }
        str run(const args& a) override { return str(); }

        int num;
    };
}

struct frameTest : public namuTest {
    frames& getFrames() {
        return (frames&) thread::get().getFrames();
    }

    void SetUp() {
        getFrames().add(new frame());
    }

    void TearDown() {
        thread::get().rel();
    }

    scopeStack& getScopeStack(frame& fr) {
        return fr._local;
    }
};

TEST_F(frameTest, testAccessFrame) {
    getFrames().add(new frame);
}

TEST_F(frameTest, testFrameManipulateChainObjNegative) {
    negative();
    frame& fr = getFrames()[getFrames().len() - 1];
    scopeStack& ss = getScopeStack(fr);
    ASSERT_FALSE(ss.getBottom().isBind());

    scope local;
    local.add("myNode1", new myNode(1));
    local.add("myNode2", new myNode(2));
    fr.pushLocal(local);
    ASSERT_TRUE(ss.getBottom().isBind());

    scopes shares;
    shares.add("myNode4", new myNode(4));
    scope owns;
    owns.add("myNode3", new myNode(3));
    ASSERT_EQ(owns.len(), 1);
    auto lambda = [](const std::string& name, const myNode& elem) {
        return true;
    };
    ASSERT_FALSE(nul(owns.get<myNode>(lambda)));

    obj obj1(shares, owns);
    ASSERT_EQ(obj1.subs().len(), 2);

    ASSERT_TRUE(ss.getBottom().isBind());
    ASSERT_EQ(fr.subAll<myNode>(lambda).len(), 2);
    ASSERT_EQ(owns.getAll<myNode>(lambda).len(), 1);
}
