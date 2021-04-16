#pragma once

#include "../interface/Instance.hpp"
#include "../bind/TBindable.hpp"

namespace wrd {

    class Chunk;
    class BindTag : public TypeProvidable, public TBindable<Instance> {
        WRD_DECL_ME(BindTag)
        WRD_INIT_META(me)
        template <typename T> friend class TWeak;
        template <typename T> friend class TStr;
        friend class WeakTactic;
        friend class StrTactic;

    public:
        //  BindTag:
        BindTag();
        explicit BindTag(Id id);
        ~BindTag();

        const Chunk& getChunk() const;
        wcnt getStrongCnt() const;
        wbool rel();
        //  TBindable:
        wbool unbind() override;
        wbool isBind() const override;
        const Type& getBindable() const;
        using TBindable::canBind;
        Instance& get() override;
        wbool canBind(const Type& cls) const override;
        wbool bind(const Instance& new1) override;
        //  Instance:
        Id getId() const;
        //  TypeProvidable:
        const Type& getType() const override{
            return TType<BindTag>::get();
        }
        static const BindTag& getBindTag(Id id);

    private:
        //  BindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(Instance& it);
        wbool _sync(Id new1);

        Instance* _pt;
        wcnt _strong;
        Id _id;
    };
}
