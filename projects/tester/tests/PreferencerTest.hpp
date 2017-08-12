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
                "   int age = 22\n"
                "   float grade=3.5\n";

            Preferencer pr;
            NE_ASSERT_THEN_RETURN( ! pr.parse(script1))
            {
                const ClassNode& preference1 = pr["preference1"];
                NE_ASSERT_THEN_RETURN(preference1.isNull())
                NE_ASSERT_THEN_RETURN(preference1.getKey() != "preference1")
                const MemberNode& member1 = preference1["grade"];
                NE_ASSERT_THEN_RETURN(member1.isNull());
                NE_ASSERT_THEN_RETURN(member1.getKey() != "grade")
                type_float EPSILON = 0.0001f;
                NE_ASSERT_THEN_RETURN(3.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
                NE_ASSERT_THEN_RETURN(member1.toString() != "3.5")
                pr.release();
                const ClassNode& preference_again = pr["preference1"];
                NE_ASSERT_THEN_RETURN( ! preference_again.isNull())
            }

            {
                NE_ASSERT_THEN_RETURN( ! pr.parse(File("resources/preferencer1.pref")))
                const ClassNode& preference1 = pr["preference1"];
                NE_ASSERT_THEN_RETURN(preference1.isNull())
                NE_ASSERT_THEN_RETURN(preference1.getKey() != "preference1")
                const MemberNode& member1 = preference1["grade"];
                NE_ASSERT_THEN_RETURN(member1.isNull());
                NE_ASSERT_THEN_RETURN(member1.getKey() != "grade")
                type_float EPSILON = 0.0001f;
                NE_ASSERT_THEN_RETURN(4.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
                NE_ASSERT_THEN_RETURN(member1.toString() != "4.5")

                const MemberNode& name = preference1["name"];
                NE_ASSERT_THEN_RETURN(name.isNull());
                NE_ASSERT_THEN_RETURN(name.toString() != "kniz")

                

                const ClassNode& food = pr["food"];
                NE_ASSERT_THEN_RETURN(food.isNull())
                NE_ASSERT_THEN_RETURN(food.getKey() != "food")
                const MemberNode& favorite = pr["food"]["favorite"];
                NE_ASSERT_THEN_RETURN(favorite.isNull())
                NE_ASSERT_THEN_RETURN(favorite.toString() != "donut")
                NE_ASSERT_THEN_RETURN(pr["food"]["count"].toInt() != 22);
            }
            
            return "";
        }
    };

    INITIATE_CLASS(PreferencerTest)
}