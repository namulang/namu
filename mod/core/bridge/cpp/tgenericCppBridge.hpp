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

    public:
        static me* def() {
            me* ret = new me(new T());
            // TODO: need to handle ctor with argument.
            ret->subs().add(baseObj::CTOR_NAME, new defaultCtor(*ret));
            ret->subs().add(baseObj::CTOR_NAME, new defaultCopyCtor(*ret));
            return ret;
        }

        template <typename Ret, typename... Args>
        me* genericFunc(const std::string& name, Ret(T::*fptr)(Args...)) {
            this->subs().add(name, new tcppBridgeFunc<Ret, T, genericCppObj, tgenericMarshaling, Args...>(fptr));
            return this;
        }
        template <typename Ret, typename... Args>
        me* genericFunc(const std::string& name, Ret(T::*fptr)(Args...) const) {
            this->subs().add(name, new tcppBridgeFunc<Ret, T, genericCppObj, tgenericMarshaling, Args...>( (Ret(T::*)(Args...)) fptr));
            return this;
        }

    };
}
