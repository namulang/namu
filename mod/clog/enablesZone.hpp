#pragma once

#include "common.hpp"

namespace namu {

    typedef std::map<std::string, nbool> enables;

    class _nout enablesZone {
        NAMU(ME(enablesZone))

    public:
        enablesZone();
        ~enablesZone();

    public:
        const enables& getPrev() const;
        void setPrev();

    private:
        enables _enables;
    };
}
