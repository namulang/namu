#include "pack.hpp"
#include "func.hpp"

namespace wrd {

    WRD_DEF_ME(pack)

    me::pack(const manifest& manifest, const packLoadings& loadingsInHeap)
        : super(manifest.name, nchain()), _loadings(loadingsInHeap), _manifest(manifest) {
            _rel();
        }

    me::~pack() {
        for(packLoading* e : _loadings) {
            e->rel();
            delete e;
        }
    }

    void me::_rel() {
        _state = RELEASED;
        _srcs.rel();
        _isValid = true;
        _rpt.bind(dummyErrReport::singletone);
        _loadings.clear();
    }

    funcs& me::getCtors() {
        static funcs inner;
        return inner;
    }
}
