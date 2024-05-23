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

        void setEnable(nbool newVal);
        void setEnable(const std::string& streamName, nbool newVal);

    private:
        enables _enables;
    };
}
