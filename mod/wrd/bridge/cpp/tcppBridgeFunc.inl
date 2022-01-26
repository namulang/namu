#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"

namespace wrd {

#define TEMPL template <typename Ret, typename T, typename... Args>
#define ME tcppBridgeFuncBase<Ret, T, Args...>

    TEMPL const wtypes& ME::getParams() const {
        static wtypes* inner = nullptr;
        if(!inner) {
            inner = new wtypes();
            inner->push_back(&ttype<tcppBridge<T>>::get());
            (inner->push_back(&ttype<typename tmarshaling<Args>::mgdType>::get()), ...);
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
