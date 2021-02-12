#pragma once

#include "../interface/Instance.hpp"

namespace wrd {

    template <typename T>
    class TBindable {
        WRD_DECL_THIS(TBindable)
        WRD_INIT_META(This)

    public:
        //  TBindable:
        virtual T* operator->();
        virtual T& operator*();
        operator wbool();

        virtual wbool bind(T& it) {
            // type checking before binding only is required to Bind class.
            // Derived classes from this doesn't need it. because its type is specified.
            // prevent wrong type providing by compiler.
            if(!canBind(it)) {
                WRD_W("can't bind it(%s) instance", it.getType().getName().c_str());
                return false;
            }
            return true;
        }
        virtual wbool unbind() = 0;
        wbool canBind(T& it);
        wbool canBind(T&& it) { return canBind(it); }
        virtual wbool canBind(Type& it) = 0;
        wbool canBind(Type&& it) { return canBind(it); }
        virtual wbool isBind() = 0;
        virtual T& get() = 0;

        template <typename E>
        E& get() {
            T& got = get();
            if(nul(got)) return nulOf<E>();

            return got.template cast<E>();
        }
    };
}
