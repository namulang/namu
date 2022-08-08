#include "src.hpp"

namespace namu {

    NAMU_DEF_ME(src)

    me::src(const std::string& fileName): _fileName(fileName) {}

    nbool me::canRun(const args& a) const { return false; }

    str me::run(const args& a) { return str(); }

    nbicontainer& me::subs() { return _subs; }

    const std::string& me::getFileName() const { return _fileName; }
}
