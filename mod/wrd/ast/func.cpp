#include "func.hpp"
#include "ref.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    tstr<narr> me::_asArgs(const ucontainable& args) {
        const params& params = getParams();
        if(args.len() != params.len())
            return WRD_E("length of args(%d) and typs(%d) doesn't match.", args.len(), params.len()),
               tstr<narr>();

        tstr<narr> ret(new narr());
        int n = 0;
        for(const node& e: args) {
            str ased = e.as(params[n++]);
            if(!ased) return tstr<narr>();

            ret->add(*ased);
        }

        return ret;
    }

    str me::run(const ucontainable& args) {
        tstr<narr> castedArgs = _asArgs(args);
        if(!castedArgs)
            return WRD_E("invalid args to call %s func.", getType().getName().c_str()), str();

        return _onCastArgs(*castedArgs);
    }

    wbool me::canRun(const ucontainable& args) const {
        const params& mine = getParams();
        wcnt len = mine.len();
        if(args.len() != len) return false;

        int n = 0;
        for(const auto& e : args)
            if(!e.isImpli(mine[n++])) return false;

        return true;
    }

    WRD_VERIFY({
        if(nul(it.getName()) || it.getName().empty())
            return _err(19);
    })
}
