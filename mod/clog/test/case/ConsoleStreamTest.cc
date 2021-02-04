#include "../common/dep.hpp"
#include <stdio.h>

using namespace std;
using namespace wrd;

typedef struct ConsoleStreamTest : public ::testing::Test {
    void SetUp() {
        delLogFile();
        ASSERT_FALSE(ConsoleStreamTest::hasLogFile());
    }
    void TearDown() {
        delLogFile();
    }

    static void delLogFile() {
        WRD_I("delLogFile");
        std::remove(getLogFilePath());
    }

    static const char* getLogFilePath() {
        static const char* name = NULL;

        if(name == NULL) {
            Logger& log = Logger::get();
            for (int n=0; n < log.getStreamCount() ;n++) {
                FileLogStream* as = dynamic_cast<FileLogStream*>(&log[n]);
                if(as) {
                    name = as->getPath().c_str();
                    break;
                }
            }
        }
        return name;
    }

    static wbool hasLogFile() {
        struct stat buffer;
        return stat(getLogFilePath(), &buffer) == 0;
    }

} ThisTest;

TEST_F(ConsoleStreamTest, dumpFormat) {
    Logger::get().dumpFormat("hello");
    Logger::get().dumpFormat("%s " WRD_TAG " %s <%s::%s#%d> " "hello",
        wrd::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), "I",
        __FILENAME__, __func__, __LINE__);

    ASSERT_TRUE(ThisTest::hasLogFile());
}

TEST_F(ConsoleStreamTest, macro) {
    ASSERT_FALSE(ThisTest::hasLogFile());

    WRD_W("world!")
    WRD_E("this is not an error.")

    ASSERT_TRUE(ThisTest::hasLogFile());
}

TEST_F(ConsoleStreamTest, debugDumpFormat) {
    wbool isDbg = BuildFeature::Config::get() == BuildFeature::DEBUG;

    WRD_DW("if it's debug mode, this msg should be shown.");

    ASSERT_EQ(isDbg, ThisTest::hasLogFile());
}
