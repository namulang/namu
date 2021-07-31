#pragma once

#include <indep.hpp>
#include <iostream>

namespace wrd {

    class interpretable {

    public:
        virtual wbool test(const wchar* msg) = 0;
    };
}
