#include "obj.hpp"
#include "func.hpp"
#include "../builtin/container/containable.inl"
#include "../frame/stackFrame.hpp"

namespace wrd {

    namespace {
        static inline std::string emptyName = "";
    }

    WRD_DEF_ME(obj)

    me::obj(): _name(&emptyName) {}
    me::obj(const string& name): _name(new string(name)) {}
    me::obj(const string& name, const nchain& subs): _subs(subs), _name(new string(name)) {}

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

    wbool me::_onInFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onInFrame()", getName().c_str());

        return fr.add(*nchain::wrapDeep(subs()));
    }

    wbool me::_onOutFrame(frame& fr, const ncontainer& args) {
        WRD_DI("%s._onOutFrame()", getName().c_str());

        fr.del();
        return true;
    }

    void me::_destruct() {
        // if we delete data, we don't have chance to set new name except making new object.
        // so this is handled inside of destruct func.
        if(_name && _name != &emptyName)
            delete _name;
    }
}
