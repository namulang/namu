#include "frameInteract.hpp"

namespace namu {

    NAMU(DEF_ME(frameInteract))

    me::frameInteract(frameInteractable& it, const bicontainable& args): _it(it) {
        _it.inFrame(args);
    }
    me::frameInteract(frameInteractable& it): _it(it) {
        _it.inFrame();
    }

    me::~frameInteract() {
        _it.outFrame();
    }
}
