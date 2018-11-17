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
            WRD_TEST( ! pr.parse(script1))
            {
                const ClassNode& preference1 = pr["preference1"];
                WRD_TEST(preference1.isNull())
                WRD_TEST(preference1.getKey() != "preference1")
                const MemberNode& member1 = preference1["grade"];
                WRD_TEST(member1.isNull());
                WRD_TEST(member1.getKey() != "grade")
                type_float EPSILON = 0.0001f;
                WRD_TEST(3.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
                WRD_TEST(member1.toString() != "3.5")
                pr.release();
                const ClassNode& preference_again = pr["preference1"];
                WRD_TEST( ! preference_again.isNull())
            }

            {
                WRD_TEST( ! pr.parse(File("resources/preferencer1.pref")))
                const ClassNode& preference1 = pr["preference1"];
                WRD_TEST(preference1.isNull())
                WRD_TEST(preference1.getKey() != "preference1")
                const MemberNode& member1 = preference1["grade"];
                WRD_TEST(member1.isNull());
                WRD_TEST(member1.getKey() != "grade")
                type_float EPSILON = 0.0001f;
                WRD_TEST(4.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
                WRD_TEST(member1.toString() != "4.5")

                const MemberNode& name = preference1["name"];
                WRD_TEST(name.isNull());
                WRD_TEST(name.toString() != "kniz")

                

                const ClassNode& food = pr["food"];
                WRD_TEST(food.isNull())
                WRD_TEST(food.getKey() != "food")
                const MemberNode& favorite = pr["food"]["favorite"];
                WRD_TEST(favorite.isNull())
                WRD_TEST(favorite.toString() != "donut")
                WRD_TEST(pr["food"]["count"].toInt() != 22);
            }
            
            return "";
        }
    };

    INITIATE_CLASS(PreferencerTest)
}
