#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/containable.inl"
#include "../frame/stackFrame.hpp"
#include "../loader/interpreter/tverification.hpp"

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

    wbool me::canRun(const containable& args) const {
        wcnt n = getCtors().getAll<func>([&args](const func& f) {
            return f.canRun(args);
        }).len();

        switch(n) {
            case 0: return WRD_E("%s object isn't constructible with given args.", getType().getName().c_str()), false;
            case 1: return true;
        }

        return WRD_E("%s object have %d ctors. it's ambigious.", getType().getName().c_str(), n), false;
    }

    void _prepareArgsAlongParam(const params& ps, narr& tray) {
        for(auto& param : ps)
            tray.add(param.getType().makeAs<node>());
    }

    WRD_VERIFY(obj, subNodes, {
        for(auto& sub : it.subs()) {
            narr tray;
            _prepareArgsAlongParam(sub.getParams(), tray);

            if(!sub.doesNeedScope()) {
                verify(sub);
                continue;
            }

            it._inFrame();
            verify(sub);
            it._outFrame();
        }
        return true;
    })
}
