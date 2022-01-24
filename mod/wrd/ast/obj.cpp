#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/containable.inl"
#include "../frame/stackFrame.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

    me::obj() {}
    me::obj(const string& name): _name(name) {}
    me::obj(const string& name, const nchain& subs): _name(name), _subs(subs) {}

    str me::run(const containable& args) {
        func& fun = getCtors().get<func>([&args](const func& candidate) {
            return candidate.canRun(args);
        });

        if(nul(fun))
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), str();

        return fun.run(args);
    }

    wbool me::canRun(const wtypes& typs) const {
        func& fun = getCtors().get<func>([&typs](const func& f) {
            return f.canRun(typs);
        });

        if(nul(fun))
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), false;
        return true;
    }
}
