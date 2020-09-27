#include "TestManager.hpp"

namespace wrd
{
#define CLASS TestManager

	const std::string& CLASS::getName() const
	{
		static std::string inner("All Tests");
		return inner;
	}

	void CLASS::put(TestCase* new1) { _tests.push_back(new1); }

	CLASS& CLASS::get()
	{
		static CLASS inner;
		return inner;
	}

	std::string CLASS::_onTest()
	{
		bool res = false;
		for(auto e : _tests)
			res = res | e->test();

		return res ? "ERROR FOUND" : "";
	}
}
