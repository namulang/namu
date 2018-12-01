#include "tests.hpp"

int main()
{
    using namespace wrd;
    using namespace std::chrono;

	milliseconds start = TestCase::getTime();

	bool res = false;
    for(auto e : TestCase::getTests())
        res = res | e->test();

	std::string msg = !res ?
		"SUCCESS" :
		"FAILURE FOUND";
	TestCase::printResult(res, "ALL TESTS", msg, TestCase::getTime()-start);
    system("pause");
	return res;
}
