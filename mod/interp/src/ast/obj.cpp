#include "obj.hpp"
#include "func.hpp"

namespace wrd {

    WRD_DEF_ME(obj)

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
