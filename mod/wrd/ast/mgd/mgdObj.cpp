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

    str me::run(const std::string& name, const containable& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());
        stackFrame& sf = wrd::thread::get()._getStackFrame();
        frame& fr = *new frame();
        sf.add(fr);
        fr.setObj(subs());

        str ret = super::run(name, args);

        WRD_DI("%s._onOutFrame()", getName().c_str());
        sf.del();
        return ret;
    }
}
