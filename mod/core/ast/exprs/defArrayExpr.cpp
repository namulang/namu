#include "defArrayExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../builtin/container/mgd/arr.hpp"

namespace namu {

    NAMU(DEF_ME(defArrayExpr), DEF_VISIT())

    str me::run(const args& a) {
        arr& ret = *new arr(getArrayType());

        for(const node& elem : _elems)
            ret.add(*elem.as<node>());

        return ret;
    }

    const node& me::getArrayType() const {
        if(!_type)
            _type = _deduceElems();

        return *_type;
    }

    str me::_deduceElems() const {
        ncnt len = items.len();
        if(!len) return nulOf<node>();

        const node* ret = &items[0];
        for(int n=1; n < len; n++)
            ret = &ret->deduce(*items[n].as<node>());

        return *ret;
    }

    const node& me::getEval() const {
        static arr inner;
        return inner;
    }

    const narr& me::getElems() const {
        return _elems;
    }
}
