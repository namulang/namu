#pragma once

#include "../interface/Instance.hpp"
#include "../bind/TBindable.hpp"

namespace wrd {

    class Chunk;
    class BindTag : public Instance, public TBindable<Instance> {
        WRD_DECL_THIS(BindTag, Instance)
        WRD_INIT_META(This)
        template <typename T> friend class TWeak;
        template <typename T> friend class TStr;
        friend class WeakTactic;
        friend class StrTactic;

    public:
        //  BindTag:
        BindTag();
        BindTag(Id id);

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
        Id getId() const override;
        wbool isHeap() const override;
        //  TypeProvidable:
        const Type& getType() const override{
            return TType<BindTag>::get();
        }

    private:
        //  BindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(Instance& it);
        wbool _sync(Id new1);

        Instance* _pt;
        wcnt _strong;
    };
}
