#include "NArr.hpp"

namespace wrd {

    WRD_DEF_THIS(NArr)

    Node& This::get(widx n) {
        if(!_isValidN(n)) return nulOf<Node>();

        return *_vec[n];
    }
    
    wbool This::set(widx n, const Node& new1) {
        if(!_isValidN(n)) return false;

        _vec[n].bind(new1);
        return true;
    }
}
