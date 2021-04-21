#pragma once

#include "../common.hpp"
#include "cast.hpp"

namespace wrd {

    class ref;
    template <typename T> class tref;
    class wtype : public type {
        WRD_DECL_ME(wtype, type)

    public:
        // wtype:
        template <typename T>
        wbool isImpli() const;
        wbool isImpli(const wtype& to) const {
            if(to.isSuper(*this)) return true;

            for(auto e : _getImplis())
                if(e->is(to)) return true;
            return false;
        }

        template <typename T>
        tref<T> asImpli(const node& it) const;
        ref asImpli(const node& it, const wtype& to) const;

        template <typename T>
        wbool is() const;
        wbool is(const wtype& type) const {
            if(isImpli(type)) return true;

            // TODO: redirection to as list.
            return false;
        }
        template <typename T>
        tref<T> as(const node& it) const;
        ref as(const node& it, const wtype& to) const;

        virtual wbool isImmutable() const {
            return false;
        }

    protected:
        // wtype:
        virtual const casts& _getImplis() const {
            static casts inner;
            return inner;
        }
    };

    typedef std::vector<const wtype*> wtypes;
}
