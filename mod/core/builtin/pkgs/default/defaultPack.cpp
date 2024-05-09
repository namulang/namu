#include "defaultPack.hpp"
#include "inputFunc.hpp"
#include "printFunc.hpp"
#include "../../primitive.hpp"

namespace namu {
    NAMU(DEF_ME(defaultPack))

    nbicontainer& me::subs() {
        static scope inner;
        if(inner.len() <= 0) {
            inner.add("input", new inputFunc());
            inner.add("print", new printFunc<nStr>());
        }
        return inner;
    }

    const baseObj& me::getOrigin() const {
        return *this;
    }
}
