#pragma once

#include <indep.hpp>

namespace wrd {

    class interpretable {

    public:
        virtual wbool test(const wchar* msg) = 0;
    };
}
