#pragma once

#include "../common.hpp"
#include <iostream>

namespace namu {

    struct _wout id {
        id(wint new_tagN, wint newChkN, wuint newSerial);
        id();

    public:
        wbool operator==(const id& rhs) const;
        wbool operator!=(const id& rhs) const;

    public:
        void rel();
        wbool isHeap() const;
        wbool isValid() const;

    public:
        wint tagN:21;
        wint chkN:22;
        wuint serial:21;
    };
}
