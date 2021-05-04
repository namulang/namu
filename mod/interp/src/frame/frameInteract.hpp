#pragma once

#include "frameInteractable.hpp"

namespace wrd {

    class frame;
    class ncontainer;
    class frameInteract {
        WRD_DECL_ME(frameInteract)
        WRD_INIT_META(frameInteract)

    public:
        frameInteract(frameInteractable& interactable, const ncontainer& args);
        virtual ~frameInteract();

    private:
        frameInteractable& _interactable;
        const ncontainer& _args;
        frame& _frame;
    };
}
