#pragma once

#include "../common.hpp"

namespace wrd {

    union Id {
        struct SeperatedId {
            wint tagN:21;
            wint chkN:22;
            wuint serial:21;
        } s;
        wint64 num;

        Id(wint64 it);
        Id(wint new_tagN = WRD_INDEX_ERROR, wint newChkN = WRD_INDEX_ERROR, wuint newSerial = 0);

        wbool operator==(const Id& rhs) const {
            return num == rhs.num;
        }
        wbool operator!=(const Id& rhs) const {
            return !operator==(rhs);
        }

        wbool isOnHeap() const {
            return s.chkN >= 0;
        }

        wbool isValid() const {
            return s.tagN >= 0;
        }
    };
}
