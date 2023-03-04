#pragma once

#include "tcppBridge.hpp"
#include "genericCppObj.hpp"

namespace namu {

    template <typename T>
    class tgenericCppBridge : public tcppBridge<T, genericCppObj> {
        typedef tcppBridge<T, genericCppObj> __super__;
        NAMU(CLASS(tgenericCppBridge, __super__))

    public:
        tgenericCppBridge(): super() {}
        tgenericCppBridge(T* real): super(real) {}
    };
}
