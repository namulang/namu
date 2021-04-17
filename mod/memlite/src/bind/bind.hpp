#pragma once

#include "tbindable.hpp"

namespace wrd {

    class bindTacticable;
    class bindTag;
    /// bind:
    ///     Overview:
    ///         can guarrantee that specific instance freed completely and track of them.
    ///         this has 3 features.
    ///             1) can distringuish what given abstract type actually was and reject or accept it regarding that.
    ///             2) free instance completely. using RAII.
    ///             3) can notice that binding instance was replaced or freed without unexpected exception.
    ///         in conlusion, it prevent halting process or give a chance to let developer be advised.
    ///
    ///     typeCheking:
    ///         me was most valuable requirement when I design component of bind.
    ///         in fact, bind was suggested to replace sort of exisiting smart-ptr concept things, such as weakptr.
    ///         because weakptr was planned to replace and enhance existing pointer of c/c++, they were very strict to
    ///         check type and whether template param T was const or not.
    ///         this characteristic was pretty worked good in most environment but not on usage of World frx.
    ///
    ///         Why was it not proper to use as before?:
    ///             World is based on class Node and make user not need to know what really was.
    ///             all actions (including calling some func on World env) can be replacable to sending msg using "use()".
    ///             To say the least, what World doing is loose-check.
    ///             so, strict type-checking of existing smart pointers doesn't matched to what Worldfrx willing to do.
    ///
    ///     Design:
    ///         bind components are mostly constructed to 3 classes and they form 2 layers vertically.
    ///         class bind:
    ///             represents binder on loose-checking layer. user can try any type to bind or get from the
    ///             binded. compiler won't complain about.
    ///             but because of loose-checking, if it's not proper request, binder will warn you at runtime as result.
    ///             constness of binding instance was persisted. (for ex, if user try to get non-const instance
    ///             from consted binder, s/he will get nulled reference.) user needs to checks that returned value
    ///             was nullref on using loose-checking API.
    ///
    ///         class TWeak, class TStr:
    ///             these represent binder on strict-checking layer.
    ///             because it was declared to class template, user need to bind or get binded using type T.
    ///             of course these are based on class bind, user can use loose-check API case by case.
    ///
    class bind : public typeProvidable, public tbindable<instance> {
        WRD_DECL_ME(bind, instance)
        WRD_INIT_META(me)
        friend class weakTactic;
        friend class strTactic;
        friend class bindTag; // for _get()

    public:
        bind(const type& type, bindTacticable& tactic);
        bind(const me& rhs);
        virtual ~bind();

        me& operator=(const me& rhs);

        //  bind:
        id getItsId() const;
        //  tbindable:
        wbool isBind() const override;
        wbool unbind() override;
        using tbindable::canBind;
        wbool canBind(const type& cls) const override;
        using tbindable::get;
        wbool bind(const instance& it) override;
        instance& get() override;
        //  typeProvidable:
        const type& getType() const override;

    protected:
        wbool _assign(const bind& rhs);
        wbool _onSame(const typeProvidable& rhs) const override;

    private:
        bindTag& _getBindTag() const;

        id _itsId; // id for binded one
        const type* _type;
        bindTacticable* _tactic;
    };
}
