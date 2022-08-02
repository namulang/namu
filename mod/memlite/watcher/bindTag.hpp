#pragma once

#include "../interface/instance.hpp"
#include "../binder/tbindable.hpp"

namespace namu {

    class chunk;
    class _wout bindTag : public typeProvidable, public tbindable<instance> {
        WRD_DECL_ME(bindTag)
        WRD_INIT_META(me)
        template <typename T, typename TACTIC> friend class tweak;
        template <typename T, typename TACTIC> friend class tstr;
        friend class weakTactic;
        friend class strTactic;

    public:
        //  bindTag:
        bindTag();
        explicit bindTag(id newId);
        ~bindTag();

    public:
        instance* operator->();
        instance& operator*();
        const instance* operator->() const WRD_UNCONST_FUNC(operator->())
        const instance& operator*() const WRD_UNCONST_FUNC(operator*())

    public:
        const chunk& getChunk() const;
        wcnt getStrongCnt() const;
        //  tbindable:
        void rel() override;
        wbool isBind() const override;
        const type& getBindable() const;
        using tbindable::canBind;

        instance& get();
        const instance& get() const WRD_UNCONST_FUNC(get())
        template <typename E>
        E& get() {
            instance& got = get();
            if(nul(got)) return nulOf<E>();

            return got.template cast<E>();
        }
        template <typename E>
        const E& get() const WRD_UNCONST_FUNC(get<E>())

        wbool canBind(const type& cls) const override;
        wbool bind(const instance& new1) override;
        //  Instance:
        id getId() const;
        //  typeProvidable:
        const type& getType() const override;
        static const bindTag& getBindTag(id newId);

    private:
        //  bindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(instance& it);
        wbool _sync(id new1);


    private:
        instance* _pt;
        wcnt _strong;
        id _id;
    };
}
