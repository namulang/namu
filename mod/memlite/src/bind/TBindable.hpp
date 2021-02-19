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
        const T* operator->() const WRD_UNCONST_FUNC(operator->())
        const T& operator*() const WRD_UNCONST_FUNC(operator*())
        operator wbool() const;

        virtual wbool bind(const T& it) {
            // type checking before binding only is required to Bind class.
            // Derived classes from this doesn't need it. because its type is specified.
            // prevent wrong type providing by compiler.
            if(!canBind(it)) {
                WRD_W("can't bind it(%s) instance", it.getType().getName().c_str());
                return false;
            }
            return true;
        }
        wbool bind(const Instance* it) { return bind(*it); }
        virtual wbool unbind() = 0;
        wbool canBind(const T& it) const;
        virtual wbool canBind(const Type& it) const = 0;
        virtual wbool isBind() const = 0;
        virtual T& get() = 0;
        const T& get() const WRD_UNCONST_FUNC(get())

        template <typename E>
        E& get() {
            T& got = get();
            if(nul(got)) return nulOf<E>();

            return got.template cast<E>();
        }
        template <typename E>
        const E& get() const WRD_UNCONST_FUNC(get<E>())
    };
}
