#include "../../frame/thread.hpp"
#include "verifier.hpp"
#include "../../frame/frame.hpp"

namespace namu {

    NAMU_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
        _frameInfo.rel();
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

    me& me::_setFrameInfo(frame& newInfo) {
        _frameInfo.bind(newInfo);
        return *this;
    }

    errReport& me::getReport() { return *_rpt; }
    frame& me::getFrameInfo() { return *_frameInfo; }

    void me::verify(node& it) {
        verify(it, it.getType());
    }

    void me::verify(node& it, const type& typ) {
        if(nul(it)) return;
        if(typ == ttype<adam>::get()) return;

        verify(it, typ.getSuper());

        verifications& veris = _getVerifications(typ);
        for(auto* elem : veris)
            elem->_onPrepareVerify(*this, it);
    }

    verifications& me::_getVerifications(const type& typ) {
        static verificationMap inner;
        return inner[(void*) &typ];
    }
}
