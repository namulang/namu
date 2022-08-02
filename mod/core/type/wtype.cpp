#include "wtype.hpp"
#include "../ast/node.hpp"
#include "../builtin/primitive.hpp"

namespace namu {

    WRD_DEF_ME(wtype)

    wbool me::isImpli(const type& to) const {
        return _getImpliAses().is(*this, to);
    }
    wbool me::isImpli(const typeProvidable& to) const { return isImpli(to.getType()); }

    str me::asImpli(const node& from, const type& to) const {
        return _getImpliAses().as(from, to);
    }

    wbool me::is(const type& to) const {
        if(isImpli(to)) return true;

        return _getAses().is(*this, to);
    }

    str me::as(const node& from, const type& to) const {
        if(isImpli(to))
            return asImpli(from, to);

        return _getAses().as(from, to);
    }

    wbool me::isImmutable() const {
        return false;
    }

    const ases& me::_getImpliAses() const {
        static ases inner;
        return inner;
    }

    const ases& me::_getAses() const {
        static ases inner;
        return inner;
    }

    const wtype& me::reduce(const wtype& r) const {
        return reduce(*this, r);
    }

    const wtype& me::reduce(const wtype& l, const wtype& r) {
        static reducers* inner = nullptr;
        if(nul(inner))
            inner = _makeReducers();

        const wtype* ret = nullptr;
        try {
            ret = inner->at(&l).at(&r);
        } catch(std::out_of_range& ex) {}

        if(!nul(ret))
            return *ret;

        return _reduceSuperType(l, r);
    }

    me::reducers* me::_makeReducers() {
        // make reduce table:
#define _X(A) &ttype<A>::get()

        reducers red = {
            {_X(wInt), {
                {_X(wInt), _X(wInt)},
                {_X(wFlt), _X(wFlt)}, // if wInt + wFlt ==> wFlt
                {_X(wStr), _X(wStr)},
                {_X(wChar), _X(wInt)},
                {_X(wBool), _X(wInt)}
            }},
            {_X(wFlt), {
                {_X(wInt), _X(wFlt)},
                {_X(wFlt), _X(wFlt)},
                {_X(wStr), _X(wStr)},
                {_X(wChar), _X(wFlt)},
                {_X(wBool), _X(wFlt)}
            }},
            {_X(wStr), {
                {_X(wInt), _X(wStr)},
                {_X(wFlt), _X(wStr)},
                {_X(wStr), _X(wStr)},
                {_X(wChar), _X(wStr)},
                {_X(wBool), _X(wStr)}
            }},
            {_X(wChar), {
                {_X(wInt), _X(wInt)},
                {_X(wFlt), _X(wFlt)},
                {_X(wStr), _X(wStr)},
                {_X(wChar), _X(wChar)},
                {_X(wBool), _X(wChar)}
            }},
            {_X(wBool), {
                {_X(wInt), _X(wInt)},
                {_X(wFlt), _X(wFlt)},
                {_X(wStr), _X(wStr)},
                {_X(wChar), _X(wInt)},
                {_X(wBool), _X(wBool)}
            }},
        };

#undef _X

        return new reducers(red);
    }

    const wtype& me::_reduceSuperType(const wtype& l, const wtype& r) {
        //  reducing super type between l & r algorithm:
        if(nul(l) || nul(r)) return nulOf<wtype>();

        const types& lAncestor = l.getSupers();
        const types& rAncestor = r.getSupers();
        wcnt lTier = lAncestor.size() - 1, // tier is the index
             rTier = rAncestor.size() - 1;
        wcnt minTier = lTier > rTier ? rTier : lTier;

        //  main:
        for(int n = minTier; n >= 0 ;n--)
            if(lAncestor[n] == rAncestor[n]) {
                const wtype& ret = (const wtype&) *lAncestor[n];
                if(ret.isSuper(ttype<node>::get()))
                    break;
                return ret;
            }

        return nulOf<wtype>();
    }
}
