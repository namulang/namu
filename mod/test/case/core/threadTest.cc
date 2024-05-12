#include "../../namuTest.hpp"

using namespace namu;

struct threadTest : public namuTest {
    void SetUp() {

    }

    void TearDown() {
        thread::get().rel();
    }
}
