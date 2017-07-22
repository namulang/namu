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
            NE_ASSERT_THEN_RETURN(logger.getStreamCount() > 0)
            NE_ASSERT_THEN_RETURN(&logger["ConsoleStream"])

            ConsoleStream* cs = new ConsoleStream();
            NE_ASSERT_THEN_RETURN(logger.pushStream(cs));
            NE_ASSERT_THEN_RETURN(logger.getStreamCount() < 1)
            NE_ASSERT_THEN_RETURN( ! &logger["ConsoleStream"])

            NE_ASSERT_THEN_RETURN(logger.dump("hello world"))

            return "";
        }
    };

    INITIATE_CLASS(LoggerTest)
}