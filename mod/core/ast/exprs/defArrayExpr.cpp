#include "defArrayExpr.hpp"
#include "../../visitor/visitor.hpp"
#include "../../builtin/container/mgd/arr.hpp"

namespace namu {

    NAMU(DEF_ME(defArrayExpr), DEF_VISIT())

    str me::run(const args& a) {
        arr& ret = *new arr(getArrayType());

        for(const node& elem : _elems)
            ret.add(*elem.as<node>());

        return (arr*) getOrigin().deepClone();
    }

    const node& me::getArrayType() const {
        return getOrigin().getElemType();
    }

    const arr& me::getOrigin() const {
        if(!_org) {
            _org.bind(new arr(*_deduceElems()));
            for(const node& e : _elems)
                _org->add(e);
        }

        return *_org;
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
        return getOrigin();
    }
}
