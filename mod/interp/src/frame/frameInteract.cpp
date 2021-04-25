#include "frameInteract.hpp"
#include "thread.hpp"
#include "frame.hpp"
#include "../builtin/container/native/ncontainer.hpp"

namespace wrd {

    WRD_DEF_ME(frameInteract)

    me::frameInteract(frameInteractable& interactable, ncontainer& args)
        :_interactable(interactable), _args(args), _frame(thread::get()._getStackFrame().getCurrentFrame()) {
        _interactable._onInFrame(_frame, _args);
    }

    me::~frameInteract() {
        _interactable._onOutFrame(_frame, _args);
    }
}
