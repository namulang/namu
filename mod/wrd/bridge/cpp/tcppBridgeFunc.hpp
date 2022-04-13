#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"

namespace wrd {

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFuncBase : public func {
        WRD(INTERFACE(tcppBridgeFuncBase, func))
    protected:
        typedef Ret (T::*fptrType)(Args...);

    public:
        tcppBridgeFuncBase(fptrType fptr): super(), _fptr(fptr) {}

        static_assert(allTrues<(sizeof(tmarshaling<Args>::canMarshal() ) == sizeof(metaIf::yes))...>::value,
            "can't marshal one of this func's parameter wtypes.");

    public:
        using super::run;
        str run(const ucontainable& args) override {
            narr evaluated = _evalArgs(args);
            return _runNative(evaluated);
        }

        const wtype& getEvalType() const override {
            return ttype<typename tmarshaling<Ret>::mgdType>::get();
        }

        const params& getParams() const override;

    protected:
        virtual str _runNative(narr& args) = 0;

    private:
        narr _evalArgs(const ucontainable& args) {
            const params& ps = getParams();
            if(args.len() != ps.len())
                return WRD_E("length of args(%d) and typs(%d) doesn't match.", args.len(), ps.len()), narr();

            narr ret;
            int n = 0;
            for(const node& e: args) {
                str ased = e.as(ps[n++].getOriginType());
                if(!ased) return narr();

                ret.add(*ased);
            }
            return ret;
        }

    protected:
        fptrType _fptr;
    };

    template <typename Ret, typename T, typename... Args>
    class tcppBridgeFunc : public tcppBridgeFuncBase<Ret, T, Args...> {
        typedef tcppBridgeFuncBase<Ret, T, Args...> __super;
        WRD(CLASS(tcppBridgeFunc, __super))

    public:
        tcppBridgeFunc(typename __super::fptrType fptr): super(fptr) {}

    protected:
        str _runNative(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };

    template <typename T, typename... Args>
    class tcppBridgeFunc<void, T, Args...> : public tcppBridgeFuncBase<void, T, Args...> {
        typedef tcppBridgeFuncBase<void, T, Args...> __super;
        WRD(CLASS(tcppBridgeFunc, __super))

    public:
        tcppBridgeFunc(typename __super::fptrType fptr): super(fptr) {}

    protected:
        str _runNative(narr& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(narr& args, std::index_sequence<index...>);
    };
}
