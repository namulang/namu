#pragma once

#include "tcppBridgeFunc.hpp"
#include "../../ast/mgd/mgdObj.hpp"

namespace wrd {

    template <typename T>
    class tcppBridge : public mgdObj {
        WRD(CLASS(tcppBridge, mgdObj))
        template <typename Ret, typename T1, typename...Args>
        friend class tcppBridgeFunc;

    private:
        tcppBridge(T* real): _real(real) {}

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
            getShares().add(new tcppBridgeFunc<Ret, T, Args...>(name, fptr));
            return this;
        }

    private:
        T* _real;
    };
}
