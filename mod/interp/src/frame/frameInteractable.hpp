#pragma once

#include "../common.hpp"

namespace wrd {

    class frame;
    class ncontainer;
    class frameInteractable {
        WRD_DECL_ME(frameInteractable)
        WRD_INIT_META(frameInteractable)
        friend class func;
        friend class obj;
        friend class frameInteract;

    protected:
        virtual wbool _onInFrame(frame& sf, ncontainer& args) = 0;
        virtual wbool _onOutFrame(frame& sf, ncontainer& args) = 0;
    };
}
