#pragma once

#include "tcppBridgeFunc.hpp"
#include "../../ast/mgd/mgdObj.hpp"

namespace wrd {

    /// bridge object only can shares 'shared' sub nodes.
    template <typename T, int lineNumber = __LINE__, const char* fileName = __FILE__>
    class tcppBridge : public obj {
        WRD(CLASS(tcppBridge, obj))
        template <typename Ret, typename T1, typename...Args>
        friend class tcppBridgeFunc;

    private:
        tcppBridge(T* real): _real(real) {
            _subs.bind(new nchain());
        }

    public:
        static me* def() {
            // TODO: need to handle ctor with argument.
            return new me(new T());
        }

        const std::string& getName() const override {
            static const std::string& inner = ttype<T>::get().getName();
            return inner;
        }

        using super::getCtors;
        funcs& getCtors() override {
            // TODO: pass real constructor of given type T.
            static funcs inner;
            return inner;
        }

        template <typename Ret, typename... Args>
        me* func(const std::string& name, Ret(T::*fptr)(Args...)) {
            subs().add(new tcppBridgeFunc<Ret, T, Args...>(name, fptr));
            return this;
        }

        const obj& getOrigin() const override {
            // if an object doesn't have owned sub nodes it means that all instances of that classes
            // are same and origin simulteneously.
            return *this;
        }

    private:
        T* _real;
    };
}
