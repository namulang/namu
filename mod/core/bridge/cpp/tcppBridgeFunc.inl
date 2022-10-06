#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"
#include "../../frame/thread.hpp"
#include "../../ast/params.hpp"

namespace namu {

#define TEMPL template <typename Ret, typename T, template <typename, nbool> class Marshaling, typename... Args>
#define ME tcppBridgeFuncBase<Ret, T, Marshaling, Args...>

    TEMPL
    const params& ME::getParams() const {
        static params* inner = nullptr;
        if(nul(inner)) {
            inner = new params();
            (inner->add(new param("", *new typename Marshaling<Args, tifSub<Args, node>::is>::mgdType())), ...);
        }

        return *inner;
    }

#undef ME
#define ME tcppBridgeFunc<Ret, T, Marshaling, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(args& a, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) a.getMe();
        if(nul(me)) return NAMU_E("object from frame does not exists."), str();

        return Marshaling<Ret, tifSub<Ret, node>::is>::toMgd((me._real->*(this->_fptr)) // funcptr
                (Marshaling<Args, tifSub<Args, node>::is>::toNative(a[index])...)); // and args.
    }

#undef ME
#undef TEMPL
#define TEMPL template <typename T, template <typename, nbool> class Marshaling, typename... Args>
#define ME tcppBridgeFunc<void, T, Marshaling, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(args& a, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) a.getMe();
        if(nul(me)) return NAMU_E("object from frame does not exists."), str();

        (me._real->*(this->_fptr))(Marshaling<Args, tifSub<Args, node>::is>::toNative(a[index])...);
        return Marshaling<void, tifSub<void, node>::is>::toMgd();
    }

#undef TEMPL
#undef ME
}
