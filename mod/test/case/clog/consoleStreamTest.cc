#include "../../common/dep.hpp"
#include <stdio.h>

using namespace std;
using namespace namu;

namespace {
    typedef struct consoleStreamTest : public ::testing::Test {
        void SetUp() {
            delLogFile();
            ASSERT_FALSE(consoleStreamTest::hasLogFile());
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
                logger& log = logger::get();
                for (int n=0; n < log.getStreamCount() ;n++) {
                    fileLogStream* as = dynamic_cast<fileLogStream*>(&log[n]);
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

    } thisTest;
}

TEST_F(consoleStreamTest, dumpFormat) {
    logger::get().dumpFormat("hello");
    logger::get().dumpFormat("%s " WRD_TAG " %s <%s::%s#%d> " "hello",
        namu::platformAPI::createNowTime("%b %d %Y  %X").c_str(), "I",
        __FILENAME__, __func__, __LINE__);

    ASSERT_TRUE(thisTest::hasLogFile());
}

TEST_F(consoleStreamTest, macro) {
    ASSERT_FALSE(thisTest::hasLogFile());

    WRD_W("world!");
    WRD_E("this is not an error.");

    ASSERT_TRUE(thisTest::hasLogFile());
}

TEST_F(consoleStreamTest, debugDumpFormat) {
    wbool isDbg = buildFeature::config::get() == buildFeature::DEBUG;

    WRD_DW("if it's debug mode, this msg should be shown.");

    ASSERT_EQ(isDbg, thisTest::hasLogFile());
}
