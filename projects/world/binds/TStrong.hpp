#include "./TWeak.hpp"

namespace wrd
{
#define TEMPL  template <typename T>
#define THIS    TStrong<T>
    TEMPL THIS::TStrong() {}
    TEMPL THIS::TStrong(T& it) : Super() { bind(it); }
    TEMPL THIS::TStrong(T* it) : Super() { bind(it); }
    TEMPL THIS::TStrong(Bindable& rhs) : Super() { bind(rhs); }

    TEMPL
    Result& THIS::bind(T& it) {
            Result& res = Super::bind(it);
            if(res) return res.dump("...");
            if( ! it.isHeap()) return InvalidParam.warn("it is local variable. couldn't bind it strongly.");

            _getInstBlk()._increaseCount();
            //  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
            //  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
            //  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
            //  bind에 의해서 해제될 수 있게 된다.
            return res;
        }
        Result& unbind() {
            InstBlk& blk = _getInstBlk();
            if(blk.isNull()) {
                InvalidMember.warn("");
                return Super::unbind();
            }
            if(blk.isHeap()) blk._decreaseCount();

    EXIT:
            return Super::unbind();
        }
    };
    //  c++11 부터 지원되는 문법
    using Strong = TStrong<Node>;
    using CStrong = TStrong<const Node>;
}
