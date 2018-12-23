#pragma once

#include "../Initiator.hpp"

WRD_TESTCASE(PreferencerTest, (
	std::string script1 = 
		"class preference1\n"
		"   int age = 22\n"
		"   float grade=3.5\n";

	Preferencer pr;
	WRD_TEST( ! pr.parse(script1))
	{
		const ClassType& preference1 = pr["preference1"];
		WRD_TEST(preference1.isNull())
		WRD_TEST(preference1.getKey() != "preference1")
		const MemberType& member1 = preference1["grade"];
		WRD_TEST(member1.isNull());
		WRD_TEST(member1.getKey() != "grade")
		wfloat EPSILON = 0.0001f;
		WRD_TEST(3.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
		WRD_TEST(member1.toStr() != "3.5")
		pr.release();
		const ClassType& preference_again = pr["preference1"];
		WRD_TEST( ! preference_again.isNull())
	}

	{
		WRD_TEST( ! pr.parse(File("resources/preferencer1.pref")))
		const ClassType& preference1 = pr["preference1"];
		WRD_TEST(preference1.isNull())
		WRD_TEST(preference1.getKey() != "preference1")
		const MemberType& member1 = preference1["grade"];
		WRD_TEST(member1.isNull());
		WRD_TEST(member1.getKey() != "grade")
		wfloat EPSILON = 0.0001f;
		WRD_TEST(4.5f + EPSILON < member1.toFloat() || member1.toFloat() < 3.5f - EPSILON)
		WRD_TEST(member1.toStr() != "4.5")

		const MemberType& name = preference1["name"];
		WRD_TEST(name.isNull());
		WRD_TEST(name.toStr() != "kniz")

		const ClassType& food = pr["food"];
		WRD_TEST(food.isNull())
		WRD_TEST(food.getKey() != "food")
		const MemberType& favorite = pr["food"]["favorite"];
		WRD_TEST(favorite.isNull())
		WRD_TEST(favorite.toStr() != "donut")
		WRD_TEST(pr["food"]["count"].toInt() != 22);
	}
	
	return "";
))
