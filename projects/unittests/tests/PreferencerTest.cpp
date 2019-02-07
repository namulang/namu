#include "../TestCase.hpp"

WRD_TEST_START(PreferencerTest)
	std::string script1 = 
		"class preference1\n"
		"   int age = 22\n"
		"   float grade=3.5\n";

	Preferencer pr;
	T(pr.parse(script1))
	{
		const ClassType& preference1 = pr["preference1"];
		T( ! preference1.isNull())
		T(preference1.getKey() == "preference1")
		const MemberType& member1 = preference1["grade"];
		T( ! member1.isNull());
		T(member1.getKey() == "grade")
		wfloat EPSILON = 0.0001f;
		T(3.5f - EPSILON <= member1.toFloat() && member1.toFloat() <= 3.5f + EPSILON) 
		T(member1.toStr() == "3.5")
		pr.release();
		const ClassType& preference_again = pr["preference1"];
		T(preference_again.isNull())
	}

	{
		T(pr.parse(File("resources/preferencer1.pref")))
		const ClassType& preference1 = pr["preference1"];
		T( ! preference1.isNull())
		T(preference1.getKey() == "preference1")
		const MemberType& member1 = preference1["grade"];
		T( ! member1.isNull());
		T(member1.getKey() == "grade")
		wfloat EPSILON = 0.0001f;
		T(4.5f - EPSILON <= member1.toFloat() && member1.toFloat() <= 4.5f + EPSILON)
		T(member1.toStr() == "4.5")

		const MemberType& name = preference1["name"];
		T( ! name.isNull());
		T(name.toStr() == "kniz")

		const ClassType& food = pr["food"];
		T( ! food.isNull())
		T(food.getKey() == "food")
		const MemberType& favorite = pr["food"]["favorite"];
		T( ! favorite.isNull())
		T(favorite.toStr() == "donut")
		T(pr["food"]["count"].toInt() == 22);
	}
	
	return "";
WRD_TEST_END(PreferencerTest)
