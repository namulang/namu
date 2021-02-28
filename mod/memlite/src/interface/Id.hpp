#pragma once

#include "../common.hpp"
#include <iostream>

namespace wrd {

    struct Id {
        Id(wint new_tagN, wint newChkN, wuint newSerial);
        Id();

        wbool operator==(const Id& rhs) const {
            return tagN == rhs.tagN && chkN == rhs.chkN && serial == rhs.serial;
        }
        wbool operator!=(const Id& rhs) const {
            return !operator==(rhs);
        }

        void rel() {
            tagN = chkN = WRD_INDEX_ERROR;
            serial = 0;
        }

        wbool isOnHeap() const {
            return chkN >= 0;
        }

        wbool isValid() const {
            return tagN >= 0;
        }

        wint tagN:21;
        wint chkN:22;
        wuint serial:21;
    };
}
