#pragma once

#include "../interface/instance.hpp"

namespace namu {

    template <typename T>
    class tbindable {
        WRD_DECL_ME(tbindable)
        WRD_INIT_META(me)

    public:
        //  tbindable:
        explicit operator wbool() const;

    public:
        virtual wbool bind(const T& it);
        wbool bind(const T* it);
        virtual void rel() = 0;
        wbool canBind(const T& it) const;
        virtual wbool canBind(const type& it) const = 0;
        virtual wbool isBind() const = 0;
    };
}
