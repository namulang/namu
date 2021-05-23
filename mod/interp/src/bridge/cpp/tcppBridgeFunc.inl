#pragma once

#include "tcppBridgeFunc.hpp"
#include "tcppBridge.hpp"

namespace wrd {

#define ME tcppBridgeFunc<Ret, T, Args...>

    template <typename Ret, typename T, typename... Args>
    template <size_t... index>
    void ME::_marshal(narr& args, std::index_sequence<index...>) {
        auto& me = (tcppBridge<T>&) args[0];

        (me._real->*_fptr)(tmarshaling<Args>::from(args[index + 1])...);
    }

    template <typename Ret, typename T, typename... Args>
    const wtypes& ME::getTypes() const {
        static wtypes* inner = nullptr;
        if(!inner) {
            inner = new wtypes();
            inner->push_back(&ttype<tcppBridge<T>>::get());
            (inner->push_back(&ttype<typename tmarshaling<Args>::marshalType>::get()), ...);
        }

        return *inner;
    }


#undef ME
}
