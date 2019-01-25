#pragma once

#include "ut-commons.hpp"

namespace wrd
{	
	#define T(expression)\
		if( ! (expression))		\
			return #expression;

	class TestCase
	{	WRD_INHERIT(TestCase)
	public:
		typedef std::vector<TestCase*> TestCases;

		bool test();
		virtual const std::string& getName() const = 0;

	protected:
		virtual std::string _onTest() = 0;

	public:
		static void printResult(bool is_success, std::string name, std::string msg, std::chrono::milliseconds process_time);
		static std::chrono::milliseconds getTime();
		static TestCases& getTests();
	};
}
