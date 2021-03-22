#pragma once

#include "../common.hpp"
#include "Asable.hpp"

namespace wrd {

    class WType : public Type, public Asable {
        WRD_DECL_THIS(WType, Type)

    public:
        // WType:
        wbool isImpliAs(const Type& to) const {
            if(to.isSuper(*this)) return true;

            for(auto e : _getImplis())
                if(e->is(to)) return true;
            return false;
        }

        Ref impliAs(const Node& inst) const;

        // Asable:
        using Asable::is;
        wbool is(const Type& type) const override {
            if(isImpliAs(type)) return true;

            // TODO: redirection to as list.
            return false;
        }
        using Asable::as;
        Ref as(const Node& it) const override;

    protected:
        // WType:
        virtual const Ases& _getImplis() const {
            static Ases inner;
            return inner;
        }
    };

    typedef std::vector<WType*> WTypes;
}
