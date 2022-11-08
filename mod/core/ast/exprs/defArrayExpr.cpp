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
        ncnt len = _elems.len();
        if(!len) return nulOf<node>();

        str ased1 = _elems[0].as<node>();
        const node* ret = &ased1.get();
        str ased;
        for(int n=1; n < len; n++) {
            ased = _elems[n].as<node>();
            ret = &ret->deduce(*ased);
        }

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
