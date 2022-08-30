#include "src.hpp"
#include "visitor.hpp"

namespace namu {

    NAMU(DEF_ME(src), DEF_VISIT())

    me::src(const std::string& fileName): _fileName(fileName) {}

    nbool me::canRun(const args& a) const { return false; }

    str me::run(const args& a) { return str(); }

    nbicontainer& me::subs() { return _subs; }

    const std::string& me::getFileName() const { return _fileName; }
}
