#include "TestManager.hpp"

void _header()
{
	using namespace std;
	//cout << "World Unittest
}

int main()
{
    using namespace wrd;
    using namespace std::chrono;

	bool res = TestManager::get().test();
    system("pause");
	return res;
}
