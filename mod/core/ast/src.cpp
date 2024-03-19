#include "src.hpp"
#include "visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(src), DEF_VISIT())

    me::src(const std::string& fileName): _fileName(fileName) {}

    priority me::prioritize(const args& a) const {
        return NO_MATCH;
    }

    str me::run(const args& a) {
        return str();
    }

    nbicontainer& me::subs() {
        static nchain inner;
        return inner;
    }

    const std::string& me::getFileName() const {
        return _fileName;
    }
}
