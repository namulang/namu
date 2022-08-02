#include "slot.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace namu {

    WRD_DEF_ME(slot)

    me::slot(const manifest& manifest): _manifest(manifest) {
        _rel();
        _pak.bind(new obj());
    }

    me::slot(const manifest& manifest, const obj& pack): _manifest(manifest) {
        _rel();
        _pak.bind(pack);
    }

    void me::_rel() {
        _dependents.rel();
        _pak.rel();
        _isValid = true;
    }

    obj& me::getPack() {
        return *_pak;
    }

    manifest& me::getManifest() { return _manifest; }
    const manifest& me::getManifest() const { return _manifest; }
    wbool me::isValid() const { return _isValid; }

    void me::rel() {
        _rel();
    }

    void me::addDependent(slot& dependent) {
        _dependents.add(dependent);
    }

    const tnarr<slot>& me::getDependents() const {
        return _dependents;
    }

    void me::_setValid(wbool valid) {
        _isValid = valid;
    }

    wbool me::_invalidate() {
        _setValid(false);

        // propagate result only if it's not valid.
        for(auto& e : _dependents)
            e._invalidate();
        return true;
    }
}
