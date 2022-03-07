#include "mgdObj.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(mgdObj)

    me& me::_assign(const me& rhs) {
        _owns = rhs._owns->deepClone();
        _subs.bind(_makeNewSubs());
        _org = rhs._org;

        return *this;
    }

    void me::_inFrame() {
        super::_inFrame();

        frame& fr = *new frame();
        fr.setObj(subs());
        wrd::thread::get()._getStackFrame().add(fr);
    }

    void me::_outFrame() {
        super::_outFrame();

        wrd::thread::get()._getStackFrame().del();
    }
}
