#pragma once

#include "frameInteractable.hpp"

namespace namu {

    class frameInteract {
        NAMU(ME(frameInteract))

    public:
        frameInteract(frameInteractable& it, const bicontainable& args): _it(it) { _it.inFrame(args); }
        frameInteract(frameInteractable& it): _it(it) { _it.inFrame(); }
        ~frameInteract() { _it.outFrame(); }

    private:
        frameInteractable& _it;
    };
}
