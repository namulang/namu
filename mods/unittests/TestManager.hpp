#pragma once

#include "TestCase.hpp"

namespace wrd
{
	class TestManager : public TestCase
	{
		typedef std::vector<TestCase*> TestCases;
	public:
		virtual const std::string& getName() const;
		const TestCases& getTests();
		void put(TestCase* new1);
		static TestManager& get();

	protected:
		virtual std::string _onTest();

	private:
		TestManager() {}
        TestCases _tests;
	};
}
