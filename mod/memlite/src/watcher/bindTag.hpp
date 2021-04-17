#pragma once

#include "../interface/instance.hpp"
#include "../binder/tbindable.hpp"

namespace wrd {

    class chunk;
    class bindTag : public typeProvidable, public tbindable<instance> {
        WRD_DECL_ME(bindTag)
        WRD_INIT_META(me)
        template <typename T> friend class tweak;
        template <typename T> friend class tstr;
        friend class weakTactic;
        friend class strTactic;

    public:
        //  bindTag:
        bindTag();
        explicit bindTag(id newId);
        ~bindTag();

        const chunk& getChunk() const;
        wcnt getStrongCnt() const;
        wbool rel();
        //  tbindable:
        wbool unbind() override;
        wbool isBind() const override;
        const type& getBindable() const;
        using tbindable::canBind;
        instance& get() override;
        wbool canBind(const type& cls) const override;
        wbool bind(const instance& new1) override;
        //  Instance:
        id getId() const;
        //  typeProvidable:
        const type& getType() const override{
            return ttype<bindTag>::get();
        }
        static const bindTag& getBindTag(id newId);

    private:
        //  bindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(instance& it);
        wbool _sync(id new1);

        instance* _pt;
        wcnt _strong;
        id _id;
    };
}
