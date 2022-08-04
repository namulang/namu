#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"

namespace namu {

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFuncBase : public func {
        NAMU(ADT(tcppBridgeFuncBase, func))
    protected:
        typedef Ret (T::*fptrType)(Args...);

    public:
        tcppBridgeFuncBase(fptrType fptr): super(), _fptr(fptr) {}

        static_assert(allTrues<(sizeof(tmarshaling<Args>::canMarshal() ) == sizeof(metaIf::yes))...>::value,
            "can't marshal one of this func's parameter ntypes.");

    public:
        using super::run;
        str run(const ucontainable& args) override {
            narr tray;
            narr& evaluated = _evalArgs(args, tray);
            if(nul(evaluated)) return NAMU_E("evaluated == null"), str();

            return _runNative(evaluated);
        }

        const node& getRet() const override {
            static typename tmarshaling<Ret>::mgdType inner;
            return inner;
        }

        const params& getParams() const override;

    protected:
        virtual str _runNative(narr& args) = 0;

    private:
        narr& _evalArgs(const ucontainable& args, narr& tray) {
            const params& ps = getParams();
            if(args.len() != ps.len())
                return NAMU_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()),
                       nulOf<narr>();

            int n = 0;
            for(const node& e: args) {
                str ased = e.as(ps[n++].getOrigin());
                if(!ased) return nulOf<narr>();

                tray.add(*ased);
            }
            return tray;
        }

    protected:
        fptrType _fptr;
    };

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFunc : public tcppBridgeFuncBase<Ret, T, Args...> {
        typedef tcppBridgeFuncBase<Ret, T, Args...> _super_;
        NAMU(CLASS(tcppBridgeFunc, _super_))

    public:
        tcppBridgeFunc(typename _super_::fptrType fptr): super(fptr) {}

    protected:
        str _runNative(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };

    template <typename T, typename... Args>
    class tcppBridgeFunc<void, T, Args...> : public tcppBridgeFuncBase<void, T, Args...> {
        typedef tcppBridgeFuncBase<void, T, Args...> _super_;
        NAMU(CLASS(tcppBridgeFunc, _super_))

    public:
        tcppBridgeFunc(typename _super_::fptrType fptr): super(fptr) {}

    protected:
        str _runNative(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };
}
