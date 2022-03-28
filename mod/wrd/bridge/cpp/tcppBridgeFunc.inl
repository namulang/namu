#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

#define TEMPL template <typename Ret, typename T, typename... Args>
#define ME tcppBridgeFuncBase<Ret, T, Args...>

    TEMPL const signature& ME::getSignature() const {
        if(!_isInit) {
            (_sig.add({"", ttype<typename tmarshaling<Args>::mgdType>::get()}), ...);
            _isInit = true;
        }

        return *inner;
    }

#undef ME
#define ME tcppBridgeFunc<Ret, T, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(narr& args, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) thread::get().getNowFrame().getObj();

        return tmarshaling<Ret>::toMgd((me._real->*(this->_fptr))(tmarshaling<Args>::toNative(args[index])...));
    }

#undef ME
#undef TEMPL
#define TEMPL template <typename T, typename... Args>
#define ME tcppBridgeFunc<void, T, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(narr& args, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) thread::get().getNowFrame().getObj();

        (me._real->*(this->_fptr))(tmarshaling<Args>::toNative(args[index])...);
        return tmarshaling<void>::toMgd();
    }

#undef TEMPL
#undef ME
}
