#include "logStructureFlag.hpp"
#include "../../cli.hpp"

namespace namu {

    NAMU_DEF_ME(logStructureFlag)

    nbool me::_onTake(const flagArgs& tray, cli& c, interpreter& ip) const {
        ip.setLogStructure(true);
        return true;
    }
}
