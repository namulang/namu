#include "dumSrc.hpp"

namespace namu {
    NAMU(DEF_ME(dumSrc))

    me::dumSrc(): super(*new srcFile("dummy", ""), "", point {0, 0}) {}

    void me::_setFile(const srcFile& new1) {}
    void me::_setPos(const point& new1) {}
    void me::_setName(const std::string& new1) {}
}
