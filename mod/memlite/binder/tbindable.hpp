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
            // type checking before binding only is required to Bind class.
            // Derived classes from this doesn't need it. because its type is specified.
            // prevent wrong type providing by compiler.
            if(!canBind(it)) return false;
            return true;
        }
        wbool bind(const instance* it) { return bind(*it); }
        virtual void rel() = 0;
        wbool canBind(const T& it) const;
        virtual wbool canBind(const type& it) const = 0;
        virtual wbool isBind() const = 0;
    };
}
