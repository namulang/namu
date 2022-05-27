#include "verification.hpp"
#include "../../ast/func.hpp"
#include "../../ast/node.hpp"
#include "verifier.hpp"
#include "../../frame/frame.hpp"

namespace wrd {

    WRD_DEF_ME(verification)

    void me::verify(typeProvidable& it) {
        _getVerifier().verify(it);
    }

    wbool me::logFrameInfo(const frame& newFr) {
        tstr<frame>& info = _verifier->getFrameInfo();
        if(nul(info)) return false;

        return info.bind(newFr);
    }
}
