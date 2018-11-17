#include "tests.hpp"
#include <iostream>

int main()
{
    using namespace NE;
    using namespace std::chrono;

	milliseconds start = TestCase::getTime();

	bool res = false;
    for(auto e : TestCase::getTests())
        res = res | e->test();

	string msg = !res ?
		"SUCCESS" :
		"FAILURE FOUND";
	TestCase::printResult(res, "ALL TESTS", msg, TestCase::getTime()-start);
    system("pause");
	return res;
}
