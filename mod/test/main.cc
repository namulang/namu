#include "common/dep.hpp"

int main(int argc, char** argv) {
    if(argc == 2 && std::string(argv[1]) == "silent") {
        namu::stream& console = namu::logger::get().getStream("consoleStream");
        console.setEnable(false);
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
