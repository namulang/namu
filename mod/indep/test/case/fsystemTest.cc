#include "../common/dep.hpp"

using namespace wrd;

TEST(fsystemTest, recursiveDirSearchAtBin) {
    // expect that workdirectory of this executable is at 'bin'.
    auto root = fsystem::find("..");
    wbool buildFound = false;

    while(root) {
        if(*root == "../build/CMakeLists.txt") {
            buildFound = true;
            break;
        }
    }
    root.rel();
    ASSERT_TRUE(buildFound);
}

TEST(fsystemTest, dirSearchWithPathEndsWithSlash) {
    auto root = fsystem::find("../");
    wbool buildFound = false;

    while(root) {
        if(*root == "../build/CMakeLists.txt") {
            buildFound = true;
            break;
        }
    }
    root.rel();
    ASSERT_TRUE(buildFound);
}
