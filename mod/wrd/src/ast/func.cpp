#include "func.hpp"
#include "ref.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    tstr<narr> me::_asArgs(const ncontainer& args) {
        const types& types = getTypes();
        if(args.len() != types.size())
            return WRD_E("length of args(%d) and types(%d) doesn't match.",
                args.len(), types.size()), tstr<narr>();

        tstr<narr> ret(new narr());
        int n = 0;
        for(const node& e: args) {
            ref ased = e.as(*types[n++]);
            if(!ased) return tstr<narr>();

            ret->add(*ased);
        }

        return ret;
    }

    str me::run(const ncontainer& args) {
        tstr<narr> castedArgs = _asArgs(args);
        if(!castedArgs) return WRD_E("invalid args to call %s func.", getType().getName().c_str()), str();

        return _onCast(*castedArgs);
    }

    const types& me::getTypes() const {
        static types inner;
        return inner;
    }

    wbool me::canRun(const types& types) const {
        const types& mine = getTypes();
        wcnt len = mine.size();
        if(types.size() != len) return false;

        for(int n=0; n < len ;n++) {
            const wtype& it = *types[n];
            const wtype& me = *mine[n];

            if(!it.isImpli(me)) return false;
        }

        return true;
    }
}
