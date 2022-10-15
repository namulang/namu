#include "../../namuTest.hpp"
#include <chrono>

using namespace namu;
using namespace std;

struct seqTest : public namuTest {};

TEST_F(seqTest, basicBehaviour) {
    nseq s(1, 10);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[9], 9);

    ASSERT_EQ(s.len(), 9);

    ASSERT_EQ(s[10], s[9]);
    ASSERT_EQ(s[-1], s[0]);
}
