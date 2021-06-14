#pragma once

#include "../interface/instance.hpp"

namespace wrd {

    template <typename T>
    class tbindable {
        WRD_DECL_ME(tbindable)
        WRD_INIT_META(me)

    public:
        //  tbindable:
        explicit operator wbool() const;

        virtual wbool bind(const T& it) {
            if(nul(it)) return false;
            // type checking before binding only is required to Bind class.
            // Derived classes from this doesn't need it. because its type is specified.
            // prevent wrong type providing by compiler.
            if(!canBind(it)) {
                WRD_W("can't bind it(%s) instance", it.getType().getName().c_str());
                return false;
            }
            return true;
        }
        wbool bind(const instance* it) { return bind(*it); }
        virtual wbool unbind() = 0;
        wbool canBind(const T& it) const;
        virtual wbool canBind(const type& it) const = 0;
        virtual wbool isBind() const = 0;
    };
}
