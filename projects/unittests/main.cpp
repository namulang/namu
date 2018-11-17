#include "tests.hpp"
#include <iostream>

int main()
{
    using namespace NE;

    for(auto e : TestCase::getTests())
        e->test();

    system("pause");
}