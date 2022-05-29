#include "verifier.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
        setPacks(thread::get().getSystemPacks());
        _frameInfo = nullptr;
    }

    me::verifier() { rel(); }

    void me::add(const verification* new1) {
        if(!new1) return;

        _getVerifications(new1->getType()).push_back(const_cast<verification*>(new1));
    }

    me& me::setReport(errReport& rpt) {
        _rpt.bind(rpt);
        return *this;
    }

    me& me::setPacks(const packContainer& packs) {
        _packs.bind(packs);
        return *this;
    }

    me& me::setFrameInfo(tstr<frame>& newInfo) {
        _frameInfo = &newInfo;
        return *this;
    }

    errReport& me::getReport() { return *_rpt; }
    tstr<frame>& me::getFrameInfo() { return *_frameInfo; }
    const packContainer& me::getPacks() { return *_packs; }

    void me::verify(typeProvidable& it) {
        _verify(it, it.getType());
    }

    void me::_verify(typeProvidable& it, const type& typ) {
        if(nul(it)) return;
        if(typ == ttype<adam>::get()) return;

        _verify(it, typ.getSuper());

        verifications& veris = _getVerifications(typ);
        for(auto* elem : veris)
            elem->verify(*this, it);
    }

    verifications& me::_getVerifications(const type& typ) {
        static verificationMap inner;
        return inner[(void*) &typ];
    }
}
