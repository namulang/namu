#include "autoslot.hpp"
#include "func.hpp"
#include "../loader/interpreter/tverification.hpp"

namespace wrd {

    WRD_DEF_ME(autoslot)

    me::autoslot(const manifest& manifest, const packLoadings& loadings): _manifest(manifest),
            _loadings(loadings) {
    }

    me::~autoslot() {
        // release all instance first:
        //  I must release allocated shared object first,
        //  before release the handle of it by releasing packLoading instance.
        rel();
    }

    void me::_rel() {
        for(auto* e : _loadings)
            delete e;
        _loadings.clear();
        state = RELEASED;
        _rpt.bind(dummyErrReport::singletone);
    }

    obj& me::getPack() {
        if(_state == RELEASED) {
            obj* new1 = new obj();
            WRD_I("%s pack is about to interpret lazy.", getManifest().name.c_str());
            // TODO: check _rpt error count increased or not.
            //       if increased, then parse() function has been failed.
            parse(*_rpt, new1->getShares()); // recursive call wasn't allowed.
            verify(*_rpt, *new1);
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

    void me::rel() {
        super::rel();
        _rel();
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

    wbool me::verify(errReport& rpt, obj& pak) {
        for(packLoading* load : _loadings)
            load->verify(rpt, pak);

        _state = VERIFIED;
        _setValid(!_rpt); // if has an error, setValid(false);
        return true;
    }

    wbool me::link() {
        _state = LINKED;
        return !isValid() ? _invalidate() : true;
    }
}
