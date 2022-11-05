#include "defArrayExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../builtin/container/mgd/arr.hpp"

namespace namu {

    NAMU(DEF_ME(defArrayExpr), DEF_VISIT())

    str me::run(const args& a) {
        arr& ret = *new arr();

        for(const node& elem : _elems)
            ret.add(*elem.as<node>());

        return ret;
    }

    const node& me::getEval() const {
        static arr inner;
        return inner;
    }

    const narr& me::getElems() const {
        return _elems;
    }
}
