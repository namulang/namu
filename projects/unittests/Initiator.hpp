#pragma once

#include "TestCase.hpp"

namespace WRD
{  
    #define INITIATE_CLASS(klass) Initiator<klass> __##klass;
    
    template <typename T>
    struct Initiator {
        Initiator() { TestCase::getTests().push_back(new T()); }
    };
}
