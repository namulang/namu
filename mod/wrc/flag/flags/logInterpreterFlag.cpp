#include "logInterpreterFlag.hpp"
#include "../../cli.hpp"

namespace wrd {

    WRD_DEF_ME(logInterpreterFlag)

    wbool me::_onTake(const args& tray, cli& c, interpreter& ip) const {
        ip.setLogInterpreter(true);
        return true;
    }
}
