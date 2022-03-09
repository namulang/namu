#include "pack.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(pack)

    me::pack(const manifest& manifest, const packLoadings& loadingsInHeap)
        : super(), _loadings(loadingsInHeap), _manifest(manifest) {
            _rel();
        }

    me::~pack() {
        // release all instance allocated inside of shared object first,
        // before release the handle of it by releasing packLoading instance.
        _subs.rel();
        for(packLoading* e : _loadings) {
            e->rel();
            delete e;
        }
    }

    void me::_rel() {
        _state = RELEASED;
        _isValid = true;
        _dependents.rel();
        _rpt.bind(dummyErrReport::singletone);
    }

    WRD_VERIFY({ // visitSubNodes
        for(auto& sub : it.subs())
            verify(sub);
    })
}
