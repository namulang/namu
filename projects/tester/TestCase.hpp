#pragma once

#include "Includes.hpp"
#include <chrono>

namespace NE
{	
	class TestCase
	{
	public:
		void test();
		virtual const char* getName() const = 0;

	protected:
		virtual bool _onTest() = 0;

	private:
		void _printResult(bool is_success, std::chrono::milliseconds process_time) const;
		std::chrono::milliseconds _getTime();

	public:
		static std::vector<TestCase*>& getTests();
	};
}