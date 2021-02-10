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
        template <typename T> friend class TWeakTactic;
        template <typename T> friend class TStrTactic;

    public:
        //  BindTag:
        BindTag();
        BindTag(Id id);

        Chunk& getChunk();
        wcnt getStrongCnt();
        wbool rel();
        //  TBindable:
        wbool unbind();
        wbool isBind();
        Type& getBindable();
        using TBindable::canBind;
        wbool canBind(Type& cls);
        //  Instance:
        Id getId();
        wbool isHeap();
        //  TypeProvidable:
        Type& getType() {
            return TType<BindTag>::get();
        }

    protected:
        //  TBindable:
        Instance& _get();
        wbool _bind(Instance& new1);

    private:
        //  BindTag:
        wbool _onStrong(wcnt vote);
        wbool _completeId(Instance& it);
        wbool _sync(Id new1);

        Instance* _pt;
        wcnt _strong;
    };
}
