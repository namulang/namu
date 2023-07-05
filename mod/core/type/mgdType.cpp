#include "mgdType.hpp"

namespace namu {

    NAMU(DEF_ME(mgdType))

    me::mgdType(const std::string& name, const narr& beans): _name(name) {
        _initSupers(ttype<obj>::get());
        getBeans() = beans;
    }

    me::mgdType(const std::string& name, const mgdType& super, const narr& beans): _name(name) {
        _initSupers(super);
        getBeans() = beans;
    }
}
