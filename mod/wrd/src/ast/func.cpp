#include "func.hpp"
#include "ref.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    tstr<narr> me::_asArgs(const containable& args) {
        const wtypes& typs = getTypes();
        if(args.len() != typs.size())
            return WRD_E("length of args(%d) and typs(%d) doesn't match.",
                args.len(), typs.size()), tstr<narr>();

        tstr<narr> ret(new narr());
        int n = 0;
        for(const node& e: args) {
            str ased = e.as(*typs[n++]);
            if(!ased) return tstr<narr>();

            ret->add(*ased);
        }

        return ret;
    }

    str me::run(const containable& args) {
        tstr<narr> castedArgs = _asArgs(args);
        if(!castedArgs) return WRD_E("invalid args to call %s func.", getType().getName().c_str()), str();

        return _onCast(*castedArgs);
    }

    const wtypes& me::getTypes() const {
        static wtypes inner;
        return inner;
    }

    wbool me::canRun(const wtypes& typs) const {
        const wtypes& mine = getTypes();
        wcnt len = mine.size();
        if(typs.size() != len) return false;

        for(int n=0; n < len ;n++) {
            const wtype& it = *typs[n];
            const wtype& me = *mine[n];

            if(!it.isImpli(me)) return false;
        }

        return true;
    }
}
