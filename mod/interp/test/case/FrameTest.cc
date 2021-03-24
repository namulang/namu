#include "../common/dep.hpp"

using namespace wrd;

struct FrameFixture : public ::testing::Test {

    void TearDown() {
        Thread::get().rel();
    }
};

TEST_F(FrameFixture, testAccessFrame) {
    StackFrame& sf = (StackFrame&) Thread::get().getStackFrame();
    sf.add(new Frame);
}
