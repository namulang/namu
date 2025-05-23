#pragma once

#include "clog/common.hpp"

namespace nm {

    typedef std::map<std::string, nbool> enables;

    class _nout enablesZone {
        NM(ME(enablesZone))

    public:
        enablesZone();
        enablesZone(nbool newVal);
        ~enablesZone();

    public:
        const enables& getPrev() const;
        me& setPrev();
        me& rel();

        me& setEnable(nbool newVal);
        me& setEnable(const std::string& streamName, nbool newVal);

    private:
        enables _enables;
    };
}
