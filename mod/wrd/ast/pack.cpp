#include "pack.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(pack)

    me::pack(const manifest& manifest, const packLoadings& loadingsInHeap)
        : _subs(*new scopes()), _loadings(loadingsInHeap), _manifest(manifest) {
            _rel();
        }

    me::~pack() {
        // release all instance first:
        //  I must release allocated shared object first,
        //  before release the handle of it by releasing packLoading instance.
        _rel();

        for(packLoading* e : _loadings) {
            e->rel();
            delete e;
        }
    }

    void me::_rel() {
        if(_state != RELEASED)
            subs().rel();
        _state = RELEASED;
        _isValid = true;
        _dependents.rel();
        _rpt.bind(dummyErrReport::singletone);
    }

    funcs& me::getCtors() {
        static funcs inner;
        return inner;
    }
}
