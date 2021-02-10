#pragma once

#include "../interface/Instance.hpp"

namespace wrd {

    template <typename T>
    class TBindable {
        WRD_DECL_THIS(TBindable)
        WRD_INIT_META(This)

    public:
        //  TBindable:
        T* operator->();
        T& operator*();
        operator wbool();

        wbool bind(T& it) { return _bind(it); }
        virtual wbool unbind() = 0;
        wbool canBind(T& it);
        wbool canBind(T&& it) { return canBind(it); }
        virtual wbool canBind(Type& it) = 0;
        wbool canBind(Type&& it) { return canBind(it); }
        virtual wbool isBind() = 0;
        T& get();

        template <typename E>
        E& get() {
            T& got = _get();
            WRD_NUL(got, nulOf<E>())

            if(!got.getType().isSub(TType<E>::get()))
                return nulOf<E>();

            return (E&) got;
        }

    protected:
        //  TBindable:
        virtual T& _get() = 0;
        virtual wbool _bind(T& it) {
            // type checking before binding only is required to Bind class.
            // Derived classes from this doesn't need it. because its type is specified.
            // prevent wrong type providing by compiler.
            if(!canBind(it)) {
                WRD_W("can't bind it(%s) instance", it.getType().getName().c_str());
                return false;
            }
            return true;
        }
    };
}
