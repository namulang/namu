#include "../common/clog-test-dep.hpp"
#include <stdio.h>
#include <filesystem>

namespace wrd { namespace clog {
#define WRD_TAG

    using namespace std::__fs;

    typedef class ConsoleStreamTest : public ::testing::Test {
    public:
        void SetUp() {
            delLogFile();
        }
        void TearDown() {
            delLogFile();
        }

        static void delLogFile() {
            WRD_I("delLogFile");
            filesystem::remove(getLogFilePath());
        }

        static const char* getLogFilePath() {
            static const char* name = NULL;

            if(name == NULL) {
                Logger& log = Logger::getInstance();
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
            return filesystem::exists(getLogFilePath());
        }

    } ThisTest;

    TEST_F(ConsoleStreamTest, dumpFormat) {
        ASSERT_FALSE(ThisTest::hasLogFile());

        Logger::getInstance().dumpFormat("hello");
        Logger::getInstance().dumpFormat("%s " WRD_TAG " %s <%s::%s#%d> " "hello",
            wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), "I",
            __FILENAME__, __func__, __LINE__);

        ASSERT_TRUE(ThisTest::hasLogFile());
    }

    TEST_F(ConsoleStreamTest, macro) {
        ASSERT_FALSE(ThisTest::hasLogFile());

        WRD_W("world!")
        WRD_E("this is not an error.")

        ASSERT_TRUE(ThisTest::hasLogFile());
    }
}}
