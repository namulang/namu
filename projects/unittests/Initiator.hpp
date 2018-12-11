#pragma once

#include "TestCase.hpp"

namespace wrd
{  
    template <typename T>
    struct Initiator {
        Initiator() { TestCase::getTests().push_back(new T()); }
    };
}
