#include "Id.hpp"

namespace wrd {

    Id::Id(wint newTagN, wint newChkN, wuint newSerial) : tagN(newTagN), chkN(newChkN), serial(newSerial) {}
    Id::Id() { rel(); }
}
