#include "verboseFlag.hpp"
#include "../../cli.hpp"

namespace namu {

    NAMU_DEF_ME(verboseFlag)

    nbool me::_onTake(const flagArgs& tray, cli& c, interpreter& ip) const {
        logger::get()["consoleStream"].setEnable(true);
        return true;
    }
}
