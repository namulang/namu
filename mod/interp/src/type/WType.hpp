#pragma once

#include "../common.hpp"
#include "As.hpp"

namespace wrd {

    class Ref;
    template <typename T> class TRef;
    class WType : public Type {
        WRD_DECL_THIS(WType, Type)

    public:
        // WType:
        template <typename T>
        wbool isImpli() const;
        wbool isImpli(const WType& to) const {
            if(to.isSuper(*this)) return true;

            for(auto e : _getImplis())
                if(e->is(to)) return true;
            return false;
        }

        template <typename T>
        TRef<T> asImpli(const Node& it) const;
        Ref asImpli(const Node& it, const WType& to) const;

        template <typename T>
        wbool is() const;
        wbool is(const WType& type) const {
            if(isImpli(type)) return true;

            // TODO: redirection to as list.
            return false;
        }
        template <typename T>
        TRef<T> as(const Node& it) const;
        Ref as(const Node& it, const WType& to) const;

    protected:
        // WType:
        virtual const Ases& _getImplis() const {
            static Ases inner;
            return inner;
        }
    };

    typedef std::vector<const WType*> WTypes;
}
