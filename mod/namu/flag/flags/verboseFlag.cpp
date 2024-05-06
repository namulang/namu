#include "verboseFlag.hpp"
#include "../../cli.hpp"

namespace namu {

    NAMU_DEF_ME(verboseFlag)

    const nchar* me::getName() const {
        return "-lv";
    }

    const nchar* me::getDescription() const {
        return R"DESC(
    prints all logs in verbose level of the interpreter.
    these are mostly about parser and verifier logs. and it includes all of process
    to tokenizing, parsing, verification.
    this info will be useful if you know how src to be interpreted.)DESC";
    }

    const nchar* me::_getRegExpr() const {
        return "^\\-lv$";
    }

    nbool me::_onTake(const flagArgs& tray, cli& c, interpreter& ip) const {
        ip.setFlag(interpreter::DEFAULT | interpreter::LOG_STRUCTURE);
        return true;
    }
}
