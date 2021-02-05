#pragma once

#include "TBindTactic.inl"
#include "../interface/Instance.hpp"

namespace wrd {

    template <typename T>
    class TWeakTactic : public TBindTactic<T> {
        WRD_DECL_THIS(TWeakTactic, TBindTactic<T>);

    public:
        wbool assign(Bind& me, const Bind& rhs) {
            if(&me == &rhs) return true;

            //    Only not available combination between this and rhs is,
            //    when this is nonconst but rhs is const.
            //    because when we accept this case, in consequence, rhs's binded one will loose their constness.
            if(!me.isConst() && rhs.isConst()) {
                WRD_W("Bind assign failed. me.const=%d but rhs.isConst()=%d", me.isConst(), rhs.isConst());
                return false; // the only case can't accept.
            }

            me._tactic = rhs._tactic;
            return me._bind(rhs.get());
        }

        wbool unbind(Bind& me) {
            me._itsId.num = WRD_INDEX_ERROR;
            return true;
        }

        wbool bind(Bind& me, const Instance& it) {
            unbind(me);
            //	regardless of result from _onStrong binder can bind:
            //		there are two reasons:
            //			because Block has equal lifecycle to what it bind, if there is
            //			a request by user to refer a bind for binding freed instance,
            //			user has responsibilty to treat wrongly.
            //			so, we should not consider such cases.
            //
            //		and:
            //			no matter how block reacts, anyway it won't refuse binder's
            //			refering. for instance, the scenario for binding non-heap allocated
            //			instance.
            me._itsId = it.getId();
            WRD_DI("Bind(%x) binds Instance(%x) of %s class",
                    &me, &it, it.getType().getName().c_str());
            return true;
        }

        static inline This singletone;
    };
}
