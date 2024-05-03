#pragma once

#include "common.hpp"

namespace namu {

    typedef std::vector<nbool> enables;

    class _nout enablesZone {
        NAMU(ME(enablesZone))

    public:
        enablesZone();
        ~enablesZone();

    private:
        enables _enables;
    };
}
