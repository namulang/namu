#pragma once

#include "tcppBridgeFunc.hpp"
#include "marshaling/tgenericMarshaling.hpp"
#include "../../ast/obj.hpp"
#include "../../type/mgdType.hpp"

namespace namu {

    /// bridge object only can shares 'shared' sub nodes.
    template <typename T>
    class tcppBridge : public obj {
        // TODO: how to impement 'as()' on bridge obj:
        //  each tcppBridge obj has its unique type object. when it got called 'getType()'
        //  it returns its type object.
        //
        //  however, type object is dynamically belongs to this bridge object, when user
        //  tries to get ttype<T>, it's not derived from ntype so it won't have any 'as()'
        //  func. user can't operate conversion in this way.
        NAMU(CLASS(tcppBridge, obj))
        template <typename Ret, typename T1, template <typename, nbool> class Marshaling, typename...Args>
        friend class tcppBridgeFunc;

    public:
        tcppBridge(): super(new mgdType(ttype<T>::get().getName())), _real(nullptr) {
            _subs.bind(new scope());
        }
        tcppBridge(T* real): super(new mgdType(ttype<T>::get().getName())), _real(real) {
            _subs.bind(new scope());
        }

    public:
        static me* def() {
            // TODO: need to handle ctor with argument.
            return new me(new T());
        }

        using super::subs;
        nbicontainer& subs() override { return *_subs; }

        template <typename Ret, typename... Args>
        me* func(const std::string& name, Ret(T::*fptr)(Args...)) {
            subs().add(name, new tcppBridgeFunc<Ret, T, tmarshaling, Args...>(fptr));
            return this;
        }
        template <typename Ret, typename... Args>
        me* func(const std::string& name, Ret(T::*fptr)(Args...) const) {
            subs().add(name, new tcppBridgeFunc<Ret, T, tmarshaling, Args...>( (Ret(T::*)(Args...)) fptr));
            return this;
        }

        template <typename Ret, typename... Args>
        me* genericFunc(const std::string& name, Ret(T::*fptr)(Args...)) {
            subs().add(name, new tcppBridgeFunc<Ret, T, tgenericMarshaling, Args...>(fptr));
            return this;
        }
        template <typename Ret, typename... Args>
        me* genericFunc(const std::string& name, Ret(T::*fptr)(Args...) const) {
            subs().add(name, new tcppBridgeFunc<Ret, T, tgenericMarshaling, Args...>( (Ret(T::*)(Args...)) fptr));
            return this;
        }

        T& get() { return *_real; }
        const T& get() const { return *_real; }

        const obj& getOrigin() const override {
            // if an object doesn't have owned sub nodes it means that all instances of that classes
            // are same and origin simulteneously.
            return *this;
        }

        // TODO: add defaultCtor, defaultCopyCtor

    private:
        T* _real;
        tstr<scope> _subs;
    };
}
