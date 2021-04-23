#include "../common/dep.hpp"

using namespace wrd;

struct frameTest : public ::testing::Test {

    void TearDown() {
        thread::get().rel();
    }
};

TEST_F(frameTest, testAccessFrame) {
    stackFrame& sf = (stackFrame&) thread::get().getStackFrame();
    sf.add(new frame);
}
