#include "id.hpp"

namespace namu {

    WRD_DEF_ME(id)

    id::id(wint newTagN, wint newChkN, wuint newSerial) : tagN(newTagN), chkN(newChkN), serial(newSerial) {}
    id::id() { rel(); }

    wbool me::operator==(const id& rhs) const {
        return tagN == rhs.tagN && chkN == rhs.chkN && serial == rhs.serial;
    }
    wbool me::operator!=(const id& rhs) const {
        return !operator==(rhs);
    }

    void me::rel() {
        tagN = chkN = WRD_INDEX_ERROR;
        serial = 0;
    }

    wbool me::isHeap() const {
        return chkN >= 0;
    }

    wbool me::isValid() const {
        return tagN >= 0;
    }
}
