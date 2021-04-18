#include "../common/dep.hpp"

using namespace wrd;

struct frameFixture : public ::testing::Test {

    void TearDown() {
        thread::get().rel();
    }
};

TEST_F(frameFixture, testAccessFrame) {
    stackFrame& sf = (stackFrame&) thread::get().getStackFrame();
    sf.add(new frame);
}
