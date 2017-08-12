#pragma once

#include <logger.hpp>
#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct LoggerTest : public TestCase {
        virtual const char* getName() const { return "LoggerTest"; }
        virtual std::string _onTest() {
            Logger& logger = Logger::getInstance();
            
            NE_ASSERT_THEN_RETURN(logger.getName() != string("Logger"))
            NE_ASSERT_THEN_RETURN(logger.getStreamCount() < 2)
            NE_ASSERT_THEN_RETURN( ! &logger["ConsoleStream"])
            NE_ASSERT_THEN_RETURN( ! &logger["FileLogStream"])

            NE_DUMP("D", "hello!")
            NE_WARN("world!")
            NE_ERROR("this is not error. paradox?")

            class MyStream : public Stream {
            public:
                virtual const char* getName() const { return "MyStream"; }
                virtual type_bool dump(const char* message) {
                    msg += message;
                    return false;
                }
                std::string msg;
            };
            MyStream* cs = new MyStream();
            NE_ASSERT_THEN_RETURN(logger.pushStream(cs));
            NE_ASSERT_THEN_RETURN(logger.getStreamCount() < 3)
            NE_ASSERT_THEN_RETURN( ! &logger["MyStream"])

            NE_ASSERT_THEN_RETURN(logger.dump("hello world"))
            NE_ASSERT_THEN_RETURN(cs->msg != "hello world")

            NE_DUMP("D", "hello!")
            NE_WARN("world!")
            NE_ERROR("this is not error. paradox?")


            type_bool found = false;
            Folder build(".", Folder::Option(false));            
            while( found || ! build.next().isNull())
                if(build.peek().getName().find("logs"))
                    found = true;

            NE_ASSERT_THEN_RETURN(found)
            NE_ASSERT_THEN_RETURN(logger.dump("let's go on 2nd phase."));

            BuildFeatures::Date date;
            NE_INFO("today is %d-%d %d. %s.", date.getMonth(), date.getDay(), date.getYear(), "Nice start!")
            NE_WARN("Fatal error! Fatal error! this PC should be infected to a virus immediatly!!!")
            NE_ERROR("***backstabbing*** It's a joke. Carm down, my master.")

            //NE_ASSERT_THEN_RETURN(logger.release()) -> can't call.            

            return "";
        }
    };

    INITIATE_CLASS(LoggerTest)
}