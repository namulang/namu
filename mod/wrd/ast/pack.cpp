#include "pack.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(pack)

    me::pack(const manifest& manifest, const packLoadings& loadingsInHeap):
            _subs(*new scopes()), _loadings(loadingsInHeap), _manifest(manifest) {
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

    nbicontainer& me::subs() {
        nbicontainer& subs = *_subs;
        if(_state == RELEASED) {
            WRD_I("%s pack is about to interpret lazy.", _manifest.name.c_str());
            // TODO: check _rpt error count increased or not.
            //       if increased, then parse() function has been failed.
            parse(*_rpt, subs); // recursive call wasn't allowed.
            verify(*_rpt, *this);
            link();
        }

        return subs;
    }

    manifest& me::getManifest() { return _manifest; }
    const manifest& me::getManifest() const { return _manifest; }
    me::state me::getState() const { return _state; }
    wbool me::isValid() const { return _isValid; }

    void me::setReport(errReport& rpt) {
        _rpt.bind(rpt);
    }

    str me::run(const ucontainable& args) { return str(); }

    wbool me::canRun(const ucontainable& args) const { return false; }

    const pack& me::getOrigin() const {
        return *this;
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

    tstr<srcs> me::parse(errReport& rpt, bicontainable& tray) {
        // You shouldn't release instances which _subs is holding:
        //  there is a scenario which _subs containing parsed instance when
        //  this function called.
        //  Only you can do here is adding new parsed instances into _subs.
        for(packLoading* load : _loadings) {
            auto res = load->parse(rpt, tray);
            _srcs.add(*res);
        }
        _state = PARSED;
        return tstr<srcs>(_srcs);
    }

    wbool me::verify(errReport& rpt, pack& pak) {
        for(packLoading* load : _loadings)
            load->verify(rpt, pak);

        _state = VERIFIED;
        return true;
    }

    wbool me::link() {
        _state = LINKED;
        return !isValid() ? invalidate() : true;
    }

    wbool me::invalidate() {
        setValid(false);
        if(_state != LINKED) return false;

        // propagate result only if it's not valid.
        for(auto& e : _dependents)
            if(e.isSub<pack>())
                e.cast<pack>().invalidate();
        return true;
    }
}