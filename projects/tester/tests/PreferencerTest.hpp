#pragma once

#include <preferencer.hpp>
#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct PreferencerTest : public TestCase {
        virtual const char* getName() const { return "PreferencerTest"; }
        virtual std::string _onTest() {
            std::string script1 = 
                "class preference1\n"
                "   age = 22\n"
                "   grade=3.5f\n"
                "   name =\t\t\t\t \"kniz\"     ";

            using namespace PR;
            Preferencer pr;
            NE_ASSERT_THEN_RETURN( ! pr.parse(script1))
            ClassNode& preference1 = pr["preference1"];
            NE_ASSERT_THEN_RETURN(Preference1.getKey() != "preference1")
            MemberNode& member1 = preference1["grade"];
            NE_ASSERT_THEN_RETURN(member1.getKey() != "grade")
            type_float EPSILON = 0.0001f;
            NE_ASSERT_THEN_RETURN(3.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
            NE_ASSERT_THEN_RETURN(member1.toString() != "3.5f")
            
            return "";
        }
    };

    INITIATE_CLASS(PreferencerTest)
}