#pragma once

#include "TWeakTactic.hpp"

namespace wrd {

    template <typename T>
    class TStrTactic : public TWeakTactic<T> {
        WRD_DECL_THIS(TStrTactic, TWeakTactic<T>);

    public:
        wbool unbind(Bind& me) {
            if(!me.isBind()) return true;

            BindTag& tag = me._getBindTag(me.getItsId());
            WRD_NUL(tag, Super::unbind(me));

            tag._onStrong(-1);
            return Super::unbind(me);
        }

        wbool bind(Bind& me, Instance& it) {
            wbool res = Super::bind(me, it);
            if(!res) {
                WRD_E("super::_bind() was failed.");
                return res;
            }

            if(!it.isHeap()) {
                WRD_W("it is local variable. couldn't bind it strongly.");
                return true;
            }

            //  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
            //  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
            //  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
            //  bind에 의해서 해제될 수 있게 된다.
            return me._getBindTag(me.getItsId())._onStrong(1);
        }

        static inline This singletone;
    };
}
