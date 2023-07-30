#include "defaultCtor.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(defaultCtor), DEF_VISIT())

    me::defaultCtor(const node& org): super(org) {}

    str me::run(const args& a) {
        if(a.len() >= 1) return str();

        return str((node*) getOrigin().clone());
    }
}
