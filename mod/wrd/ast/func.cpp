#include "func.hpp"
#include "ref.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(func)

    tstr<narr> me::_asArgs(const ucontainable& args) {
        const signature& sig = getSignature();
        if(args.len() != sig.len())
            return WRD_E("length of args(%d) and typs(%d) doesn't match.", args.len(), sig.len()),
               tstr<narr>();

        tstr<narr> ret(new narr());
        int n = 0;
        for(const node& e: args) {
            str ased = e.as(sig[n++].type);
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
        const sig& sig = getSignature();
        if(args.len() != sig.len) return false;

        int n = 0;
        for(const auto& e : args)
            if(!e.isImpli(sig[n++].type)) return false;

        return true;
    }

    WRD_VERIFY({
        const std::string& name = it.getSignature().get();
        if(nul(name) || name.empty())
            return _err(19);
    })
}
