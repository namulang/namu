#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace NE
{	
	#define WRD_TEST(expression)	\
		if(expression)						\
			return #expression;

	class TestCase
	{
	public:
		typedef std::vector<TestCase*> TestCases;

		void test();
		virtual const char* getName() const = 0;

	protected:
		virtual std::string _onTest() = 0;

	private:
		void _printResult(std::string result, std::chrono::milliseconds process_time) const;
		std::chrono::milliseconds _getTime();

	public:
		static TestCases& getTests();
	};
}
