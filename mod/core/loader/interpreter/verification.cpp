#include "verification.hpp"
#include "../../ast/func.hpp"
#include "../../ast/node.hpp"
#include "verifier.hpp"
#include "../../frame/frame.hpp"

namespace namu {

    NAMU_DEF_ME(verification)

    void me::verify(node& it) {
        nmap tray;
        verify(it, tray);
    }

    void me::verify(node& it, bicontainable& tray) {
        getVerifier().verify(it, tray);
    }

    nbool me::logFrameInfo(const frame& newFr) {
        tstr<frame>& info = _verifier->getFrameInfo();
        if(nul(info)) return false;

        return info.bind(newFr);
    }

    verifier& me::getVerifier() { return *_verifier; }
    bicontainable& me::getTray() { return *_tray; }
    node& me::_getIt() { return *_it; }
}
