#pragma once

#include "ut-commons.hpp"

namespace wrd
{
	#define T(expression)\
		if( ! (expression))		\
			return "(#" WRD_TO_STR(__LINE__) ") " #expression;

	class TestCase
	{	WRD_INHERIT(TestCase)
	public:
		virtual const std::string& getName() const = 0;
		virtual bool test();
		std::string getHeader() const;
		std::chrono::milliseconds getTime() const;

	protected:
		virtual std::string _onTest() = 0;
		void _printResult(bool is_success, std::string msg);
		std::chrono::milliseconds _start;
	};
}
