#include "NArr.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    WRD_DEF_THIS(NArr)

    Node& This::get(widx n) {
        if(!_isValidN(n)) return nulOf<Node>();

        return *_vec[n];
    }

    wbool This::set(const Iter& at, const Node& new1) {
        auto cast = at._step->cast<NArrIteration>();
        if(nul(cast)) return false;

        return set(cast._n, new1);
    }


    wbool This::set(widx n, const Node& new1) {
        if(!_isValidN(n)) return false;

        _vec[n].bind(new1);
        return true;
    }

    wbool This::add(const Iter& e, const Node& new1) {
        if(!Super::add(e, new1)) return false;
        NArrIteration& cast = (NArrIteration&) e._step;

        widx n = cast._n;
        _vec.insert(_vec.begin() + n, Str(new1));
        return true;
    }

    wbool This::del(const Iter& it) {
        if(!Super::del(it)) return false;
        NArrIteration& cast = (NArrIteration&) it._step;

        _vec.erase(_vec.begin() + cast._n);
        return true;
    }

    wcnt This::getLen() const {
        return _vec.size();
    };

    void This::empty() {
        _vec.clear();
    }
}
