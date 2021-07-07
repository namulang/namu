#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

namespace {

}

TEST(packLoaderTest, testCppPackMakingExist) {
    manifest cppMani("test", "/test/path", "Michel Jackson", "2553923.0.1",
        entrypoints { entrypoint("cpp", std::vector<std::string> {"/some/path.pack"}) }
    );
    tstr<pack> made(packMaker().makeWith(cppMani));
    ASSERT_TRUE(made);
    ASSERT_TRUE(made->isSub<cppPack>());
}

TEST(packLoaderTest, testDefaultLoaderInit) {
    wrd::thread::get().getSystemPackLoader();
}


TEST(packLoaderTest, testLoadSamplePack) {
    packLoader loader("pack");

    const node& pack = loader["samplePack"][0];
    ASSERT_FALSE(nul(pack));

    //pak["demoClass"]
}
