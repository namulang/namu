#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"

namespace wrd {

#define TEMPL template <typename Ret, typename T, typename... Args>
#define ME tcppBridgeFuncBase<Ret, T, Args...>

    TEMPL const params& ME::getParams() const {
        static params* inner = nullptr;
        if(!inner) {
            inner = new params();
            inner->add(new ref(ttype<tcppBridge<T>>::get()));
            (inner->add(new ref(ttype<typename tmarshaling<Args>::mgdType>::get())), ...);
        }

        return *inner;
    }

#undef ME
#define ME tcppBridgeFunc<Ret, T, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(narr& args, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) args[0];

        return tmarshaling<Ret>::toMgd((me._real->*(this->_fptr))(tmarshaling<Args>::toNative(args[index + 1])...));
    }

#undef ME
#undef TEMPL
#define TEMPL template <typename T, typename... Args>
#define ME tcppBridgeFunc<void, T, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(narr& args, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) args[0];

        (me._real->*(this->_fptr))(tmarshaling<Args>::toNative(args[index + 1])...);
        return tmarshaling<void>::toMgd();
    }

#undef TEMPL
#undef ME
}
