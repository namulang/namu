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

        Chunk& getChunk();
        wcnt getStrongCnt();
        wbool rel();
        //  TBindable:
        wbool unbind() override;
        wbool isBind() override;
        Type& getBindable();
        using TBindable::canBind;
        wbool canBind(Type& cls) override;
        Instance& get() override;
        wbool bind(Instance& new1) override;
        //  Instance:
        Id getId() override;
        wbool isHeap() override;
        //  TypeProvidable:
        Type& getType() override{
            return TType<BindTag>::get();
        }

    protected:

    private:
        //  BindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(Instance& it);
        wbool _sync(Id new1);

        Instance* _pt;
        wcnt _strong;
    };
}
