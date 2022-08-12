#pragma once

#include "../../ast/func.hpp"
#include "marshaling.hpp"
#include "../../ast/args.hpp"

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
        str run(const args& a) override {
            args tray;
            args& evaluated = _evalArgs(a, tray);
            if(nul(evaluated)) return NAMU_E("evaluated == null"), str();

            return _runNative(evaluated);
        }

        const node& getRet() const override {
            static typename tmarshaling<Ret>::mgdType inner;
            return inner;
        }

        const params& getParams() const override;

    protected:
        virtual str _runNative(args& args) = 0;

    private:
        args& _evalArgs(const args& a, args& tray) {
            const params& ps = getParams();
            if(a.len() != ps.len())
                return NAMU_E("length of a(%d) and typs(%d) doesn't match.", a.len(), ps.len()),
                       nulOf<args>();

            int n = 0;
            for(const node& e: a) {
                str ased = e.as(ps[n++].getOrigin());
                if(!ased) return nulOf<args>();

                tray.add(*ased);
            }
            tray.setMe(a.getMe());
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
        str _runNative(args& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(args& args, std::index_sequence<index...>);
    };

    template <typename T, typename... Args>
    class tcppBridgeFunc<void, T, Args...> : public tcppBridgeFuncBase<void, T, Args...> {
        typedef tcppBridgeFuncBase<void, T, Args...> _super_;
        NAMU(CLASS(tcppBridgeFunc, _super_))

    public:
        tcppBridgeFunc(typename _super_::fptrType fptr): super(fptr) {}

    protected:
        str _runNative(args& args) override {
            return _marshal(args, std::index_sequence_for<Args...>());
        }

        template <size_t... index>
        str _marshal(args& args, std::index_sequence<index...>);
    };
}
