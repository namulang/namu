#pragma once

#include "frameInteractable.hpp"

namespace wrd {

    class frame;
    class containable;
    class frameInteract {
        WRD_DECL_ME(frameInteract)
        WRD_INIT_META(frameInteract)

    public:
        frameInteract(frameInteractable& interactable, const containable& args);
        virtual ~frameInteract();

    private:
        frameInteractable& _interactable;
        const containable& _args;
        frame& _frame;
    };
}
