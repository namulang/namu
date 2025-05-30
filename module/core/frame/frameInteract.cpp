#include "core/frame/frameInteract.hpp"

namespace nm {

    NM(DEF_ME(frameInteract))

    me::frameInteract(const frameInteractable& it, const bicontainable& args):
        _it(it), _args(args) {
        if(!nul(it)) _it.inFrame(_args);
    }

    me::frameInteract(const frameInteractable& it): _it(it), _args(nulOf<bicontainable>()) {
        if(!nul(it)) _it.inFrame();
    }

    me::~frameInteract() { _it.outFrame(_args); }
}
