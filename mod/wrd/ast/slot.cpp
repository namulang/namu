#include "slot.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(slot)

    me::slot(const manifest& manifest): _manifest(manifest) {
        _rel();
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

    wbool me::setPack(const obj& newPack) {
        return _pak.bind(newPack);
    }

    manifest& me::getManifest() { return _manifest; }
    const manifest& me::getManifest() const { return _manifest; }
    wbool me::isValid() const { return _isValid; }

    void me::setReport(errReport& rpt) {
        _rpt.bind(rpt);
    }

    void me::rel() {
        super::rel();
        _rel();
    }

    void me::addDependent(pack& dependent) {
        _dependents.add(dependent);
    }

    const tnarr<pack>& me::getDependents() const {
        return _dependents;
    }

    void me::setValid(wbool valid) {
        _isValid = valid;
    }

    wbool me::_invalidate() {
        if(_state != LINKED) return false;

        // propagate result only if it's not valid.
        for(auto& e : _dependents)
            if(e._invalidate();
        return true;
    }
}
