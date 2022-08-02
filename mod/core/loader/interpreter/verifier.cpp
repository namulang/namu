#include "../../frame/thread.hpp"
#include "verifier.hpp"

namespace namu {

    NAMU_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
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

    me& me::setFrameInfo(tstr<frame>& newInfo) {
        _frameInfo = &newInfo;
        return *this;
    }

    errReport& me::getReport() { return *_rpt; }
    tstr<frame>& me::getFrameInfo() { return *_frameInfo; }

    void me::verify(node& it) {
        nmap m;
        verify(it, it.getType(), m);
    }

    void me::verify(node& it, bicontainable& tray) {
        verify(it, it.getType(), tray);
    }

    void me::verify(node& it, const type& typ, bicontainable& tray) {
        if(nul(it)) return;
        if(typ == ttype<adam>::get()) return;

        verify(it, typ.getSuper(), tray);

        verifications& veris = _getVerifications(typ);
        for(auto* elem : veris)
            elem->_onPrepareVerify(*this, it, tray);
    }

    verifications& me::_getVerifications(const type& typ) {
        static verificationMap inner;
        return inner[(void*) &typ];
    }
}
