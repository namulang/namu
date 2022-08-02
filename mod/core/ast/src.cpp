#include "src.hpp"

namespace namu {

    WRD_DEF_ME(src)

    me::src(const std::string& fileName): _fileName(fileName) {}

    wbool me::canRun(const ucontainable& args) const { return false; }

    str me::run(const ucontainable& args) { return str(); }

    nbicontainer& me::subs() { return _subs; }

    const std::string& me::getFileName() const { return _fileName; }
}
