#include "obj.hpp"
#include "../frame/stackFrame.hpp"
#include "func.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(subs());
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        return fr.del();
    }

    me& me::_assign(const me& rhs) {
        if(this == &rhs) return *this;

        _shares = rhs._shares;
        _owns = rhs._owns->deepClone();
        _subs.bind(new nchain(*_owns));
        _subs->link(*_shares);

        return *this;
    }

    str me::run(const ncontainer& args) {
        tnarr<func> candidates = getCtors().get<func>([&args](const func& candidate) {
            return candidate.canRun(args);
        });

        if(candidates.len() != 1)
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), str();

        return candidates[0].run(args);
    }

    wbool me::canRun(const wtypes& types) const {
        tnarr<func> candidates = getCtors().get<func>([&types](const func& f) {
            return f.canRun(types);
        });

        if(candidates.len() != 1)
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), false;
        return true;
    }

}
