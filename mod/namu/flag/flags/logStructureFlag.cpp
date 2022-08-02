#include "logStructureFlag.hpp"
#include "../../cli.hpp"

namespace namu {

    WRD_DEF_ME(logStructureFlag)

    wbool me::_onTake(const args& tray, cli& c, interpreter& ip) const {
        ip.setLogStructure(true);
        return true;
    }
}
