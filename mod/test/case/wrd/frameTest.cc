#include "../../common/dep.hpp"

using namespace wrd;

namespace {
    struct myNode : public node {
        WRD(CLASS(myNode, node))

    public:
        myNode(int n): num(n) {}

        nucontainer& subs() override { return nulOf<nucontainer>(); }
        wbool canRun(const ucontainable& types) const override { return false; }
        str run(const ucontainable& args) override { return str(); }

        int num;
    };
}

struct frameTest : public ::testing::Test {
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
    frame& fr = getFrames()[getFrames().len() - 1];
    scopeStack& ss = getScopeStack(fr);
    ASSERT_FALSE(ss.getBottom().isBind());

    nchain local;
    local.add(new myNode(1));
    local.add(new myNode(2));
    fr.pushLocal(local);
    ASSERT_TRUE(ss.getBottom().isBind());

    nchain shares;
    shares.add(new myNode(4));
    nchain owns;
    owns.add(new myNode(3));
    owns.link(shares);
    ASSERT_EQ(owns.len(), 2);
    auto lambda = [](const myNode& elem) {
        return true;
    };
    ASSERT_FALSE(nul(owns.get<myNode>(lambda)));

    fr.setObj(*nchain::wrapDeep(owns));
    ASSERT_TRUE(ss.getBottom().isBind());
    ASSERT_EQ(fr.subAll<myNode>(lambda).len(), 4);
    ASSERT_EQ(owns.getAll<myNode>(lambda).len(), 2);

    int expects[] = {1, 2, 3, 4};
    titer<myNode> e = ss.getTop()->begin<myNode>();
    for (int expect : expects) {
        ASSERT_EQ(expect, e->num);
        ++e;
    }
}
