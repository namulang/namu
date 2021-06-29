#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {

}

TEST(packLoaderTest, testDefaultLoaderInit) {
    wrd::thread::get().getSystemPackLoader();
}
