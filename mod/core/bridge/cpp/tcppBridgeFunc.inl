#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"
#include "../../frame/thread.hpp"
#include "../../ast/params.hpp"

namespace namu {

#define TEMPL template <typename Ret, typename T, typename S, template <typename, typename, nbool> class Marshaling, typename... Args>
#define ME tcppBridgeFuncBase<Ret, T, S, Marshaling, Args...>

    TEMPL
    const params& ME::getParams() const {
        if(!_params) {
            _params.bind(new params());
            (_params->add(new param("", Marshaling<Args, S, tifSub<Args, node>::is>::onAddParam())), ...);
        }

        return *_params;
    }

#undef ME
#define ME tcppBridgeFunc<Ret, T, S, Marshaling, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(args& a, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) a.getMe();
        if(nul(me)) return NAMU_E("object from frame does not exists."), str();

        return Marshaling<Ret, S, tifSub<Ret, node>::is>::toMgd((me._real->*(this->_fptr)) // funcptr
                (Marshaling<Args, S, tifSub<Args, node>::is>::toNative(a[index])...)); // and args.
    }

#undef ME
#undef TEMPL
#define TEMPL template <typename T, typename S, template <typename, typename, nbool> class Marshaling, typename... Args>
#define ME tcppBridgeFunc<void, T, S, Marshaling, Args...>

    TEMPL
    template <size_t... index>
    str ME::_marshal(args& a, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) a.getMe();
        if(nul(me)) return NAMU_E("object from frame does not exists."), str();

        (me._real->*(this->_fptr))(Marshaling<Args, S, tifSub<Args, node>::is>::toNative(a[index])...);
        return Marshaling<void, S, tifSub<void, node>::is>::toMgd();
    }

#undef TEMPL
#undef ME
}
