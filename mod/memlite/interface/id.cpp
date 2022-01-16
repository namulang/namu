#include "id.hpp"

namespace wrd {

    id::id(wint newTagN, wint newChkN, wuint newSerial) : tagN(newTagN), chkN(newChkN), serial(newSerial) {}
    id::id() { rel(); }
}
