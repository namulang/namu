#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"

namespace wrd {

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFunc : public func {
        WRD_CLASS(tcppBridgeFunc, func)
        typedef Ret (T::*fptrType)(Args...);

    public:
        tcppBridgeFunc(const std::string& name, fptrType fptr): super(name), _fptr(fptr) {}

        static_assert(allTrues<(sizeof(tmarshaling<Args>::canMarshal() ) == sizeof(metaIf::yes))...>::value, "can't marshal one of this func's parameter types.");

    protected:
        str _onCast(narr& args) override {
            _marshal(args, std::index_sequence_for<Args...>());
            // TODO: need to handle return value.
            return str();
        }
        wbool _onInFrame(frame& sf, const ncontainer& args) override { return true; }
        wbool _onOutFrame(frame& sf, const ncontainer& args) override { return true; }

        const wtype& getReturnType() const override {
            // TODO: return primitive type by ttype too.
            return ttype<wInt>::get();
        }

        const wtypes& getTypes() const override;

    private:
        template <size_t... index>
        void _marshal(narr& args, std::index_sequence<index...>);

    private:
        fptrType _fptr;
    };
}
