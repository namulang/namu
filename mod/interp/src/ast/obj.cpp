#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/containable.inl"

namespace wrd {

    WRD_DEF_ME(obj)

    me::obj(const std::string& name, const narr& subItself)
        : _name(name), _subs(new nchain(subItself)) {}

    str me::run(const ncontainer& args) {
        func& fun = getCtors().get<func>([&args](const func& candidate) {
            return candidate.canRun(args);
        });

        if(nul(fun))
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), str();

        return fun.run(args);
    }

    wbool me::canRun(const wtypes& types) const {
        func& fun = getCtors().get<func>([&types](const func& f) {
            return f.canRun(types);
        });

        if(nul(fun))
            return WRD_E("%s object isn't constructable with given args", getType().getName().c_str()), false;
        return true;
    }

}
