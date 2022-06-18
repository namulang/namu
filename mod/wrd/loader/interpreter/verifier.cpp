#include "../../frame/thread.hpp"
#include "verifier.hpp"

namespace wrd {

    WRD_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
        setSlots(thread::get().getSystemSlots());
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

    me& me::setSlots(const tnbicontainer<std::string, slot>& slots) {
        _slots.bind(slots);
        return *this;
    }

    me& me::setFrameInfo(tstr<frame>& newInfo) {
        _frameInfo = &newInfo;
        return *this;
    }

    errReport& me::getReport() { return *_rpt; }
    tstr<frame>& me::getFrameInfo() { return *_frameInfo; }
    const slotContainer& me::getSlots() { return *_slots; }

    void me::verify(node& it) {
        _verify(it, it.getType());
    }

    void me::_verify(node& it, const type& typ) {
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
