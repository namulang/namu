#pragma once

#include <functional>

#include "../../ast/args.hpp"
#include "../../ast/baseFunc.hpp"
#include "../../ast/params.hpp"

namespace nm {

    template <typename Ret, typename T, template <typename, nbool> class Marshaling,
        typename... Args>
    class tbridgeClosure: public baseFunc {
        NM(ME(tbridgeClosure, baseFunc), CLONE(tbridgeClosure))
        static_assert(allTrues<(sizeof(Marshaling<Args, tifSub<Args, node>::is>::canMarshal()) ==
                          sizeof(metaIf::yes))...>::value,
            "can't marshal one of this func's parameter ntypes.");

    public:
        tbridgeClosure(std::function<Ret(T&, Args...)> closure): _closure(closure) {}

    public:
        using super::run;

        const ntype& getType() const override {
            static mgdType inner("ctor", ttype<me>::get(),
                params(*new param("", Marshaling<Args, tifSub<Args, node>::is>::onAddParam())...));
            return inner;
        }

        str run(const args& a) override {
            args tray;
            args& evaluated = _evalArgs(a, tray);
            if(nul(evaluated)) return NM_E("evaluated == null"), str();

            return _marshal(evaluated, std::index_sequence_for<Args...>());
        }

        str getRet() const override {
            static str ret(
                Marshaling<Ret, tifSub<typename typeTrait<Ret>::Org, node>::is>::onGetRet());
            return ret;
        }

    private:
        template <size_t... index> str _marshal(args& a, std::index_sequence<index...>) {
            T* me = (T*) &a.getMe();
            if(nul(me)) return NM_E("object from frame does not exists."), str();

            return Marshaling<Ret, tifSub<typename typeTrait<Ret>::Org, node>::is>::toMgd(
                _closure(*me, Marshaling<Args, tifSub<Args, node>::is>::toNative(a[index])...));
        }

        args& _evalArgs(const args& a, args& tray) {
            const params& ps = getParams();
            if(a.len() != ps.len())
                return NM_E("length of a(%d) and typs(%d) doesn't match.", a.len(), ps.len()),
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

    private:
        std::function<Ret(T&, Args...)> _closure;
    };

    template <typename T, template <typename, nbool> class Marshaling, typename... Args>
    class tbridgeClosure<void, T, Marshaling, Args...>: public baseFunc {
        NM(ME(tbridgeClosure, baseFunc), CLONE(tbridgeClosure))
        static_assert(allTrues<(sizeof(Marshaling<Args, tifSub<Args, node>::is>::canMarshal()) ==
                          sizeof(metaIf::yes))...>::value,
            "can't marshal one of this func's parameter ntypes.");

    public:
        tbridgeClosure(std::function<void(T&, Args...)>&& closure): _closure(closure) {}

    public:
        const ntype& getType() const override {
            static mgdType inner("ctor", ttype<me>::get(),
                params(*new param("", Marshaling<Args, tifSub<Args, node>::is>::onAddParam())...));
            return inner;
        }

        using super::run;

        str run(const args& a) override {
            args tray;
            args& evaluated = _evalArgs(a, tray);
            if(nul(evaluated)) return NM_E("evaluated == null"), str();

            return _marshal(evaluated, std::index_sequence_for<Args...>());
        }

        str getRet() const override {
            static str ret(Marshaling<void, false>::onGetRet());
            return ret;
        }

    private:
        template <size_t... index> str _marshal(args& a, std::index_sequence<index...>) {
            T* me = (T*) &a.getMe();
            if(nul(me)) return NM_E("object from frame does not exists."), str();

            _closure(*me, Marshaling<Args, tifSub<Args, node>::is>::toNative(a[index])...);
            return Marshaling<void, tifSub<void, node>::is>::toMgd();
        }

        args& _evalArgs(const args& a, args& tray) {
            const params& ps = getParams();
            if(a.len() != ps.len())
                return NM_E("length of a(%d) and typs(%d) doesn't match.", a.len(), ps.len()),
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

    private:
        std::function<void(T&, Args...)> _closure;
    };
} // namespace nm
