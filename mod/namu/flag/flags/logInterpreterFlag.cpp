#include "logInterpreterFlag.hpp"
#include "../../cli.hpp"

namespace namu {

    NAMU_DEF_ME(logInterpreterFlag)

    nbool me::_onTake(const flagArgs& tray, cli& c, interpreter& ip) const {
        ip.setLogInterpreter(true);
        return true;
    }
}
