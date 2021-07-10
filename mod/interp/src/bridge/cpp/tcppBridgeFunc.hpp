#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"

namespace wrd {

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFuncBase : public func {
        WRD_CLASS(tcppBridgeFuncBase, func)
        typedef Ret (T::*fptrType)(Args...);

    public:
        tcppBridgeFuncBase(const std::string& name, fptrType fptr): super(name), _fptr(fptr) {}

        static_assert(allTrues<(sizeof(tmarshaling<Args>::canMarshal() ) == sizeof(metaIf::yes))...>::value, "can't marshal one of this func's parameter types.");

    protected:
        wbool _onInFrame(frame& sf, const ncontainer& args) override { return true; }
        wbool _onOutFrame(frame& sf, const ncontainer& args) override { return true; }

        const wtype& getReturnType() const override {
            return ttype<typename tmarshaling<Ret>::mgdType>::get();
        }

        const wtypes& getTypes() const override;

    private:
        fptrType _fptr;
    };

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFunc : public tcppBridgeFuncBase<Ret, T, Args...> {
        WRD_CLASS(tcppBridgeFunc, WRD_DELAY(tcppBridgeFuncBase<Ret, T, Args...>))

    public:
        tcppBridgeFunc(const std::string& name, fptrType fptr): super(name, fptr) {}

    protected:
        str _onCast(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

    private:
        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };

    template <typename T, typename... Args>
    class tcppBridgeFunc<void> : public tcppBridgeFuncBase<Ret, T, Args...> {
        WRD_CLASS(tcppBridgeFunc, tcppBridgeFuncBase<Ret, T, Args...>)

    public:
        tcppBridgeFunc(const std::string& name, fptrType fptr): super(name, fptr) {}

    protected:
        str _onCast(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

    private:
        template <size_t... index>
        str _marshal(narr& args, std::index_sequnce<index...>);
    };
}
