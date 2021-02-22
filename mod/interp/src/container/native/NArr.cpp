#include "NArr.hpp"
#include "../../ast/Node.hpp"

namespace wrd {

    WRD_DEF_THIS(NArr)

    Node& This::get(widx n) {
        if(!_isValidN(n)) return nulOf<Node>();

        Bind& ret = _vec[n];
        return (Node&) *ret;
    }

    wbool This::set(const Iter& at, const Node& new1) {
        auto cast = at._step->cast<NArrIteration>();
        if(nul(cast)) return false;

        return set(cast._n, new1);
    }

    wbool This::_isValidN(widx n) const {
        return 0 <= n && n < getLen();
    }

    wbool This::set(widx n, const Node& new1) {
        if(!_isValidN(n)) return false;

        _vec[n].bind(new1);
        return true;
    }

    wbool This::add(const Iter& e, const Node& new1) {
        if(nul(e) || nul(new1)) return false;
        if(!e.isFrom(*this)) return false;
        NArrIteration& cast = (NArrIteration&) *e._step;

        return add(cast._n, new1);
    }

    wbool This::add(widx n, const Node& new1) {
        if(n < 0 || n > getLen()) return false; // if n equals to getLen(), it means that will be added at end of container.

        Str wrap(new1);
        if(!wrap) return false;
        _vec.insert(_vec.begin() + n, Str(new1));
        return true;
    }

    wbool This::del(const Iter& it) {
        if(nul(it)) return false;
        if(!it.isFrom(*this)) return false;
        if(it.isEnd()) return false;
        NArrIteration& cast = (NArrIteration&) *it._step;

        _vec.erase(_vec.begin() + cast._n);
        return del(cast._n);
    }

    wbool This::del(widx n) {
        if(!_isValidN(n)) return false;
        _vec.erase(_vec.begin() + n);
        return true;
    }

    wcnt This::getLen() const {
        return _vec.size();
    };

    void This::empty() {
        _vec.clear();
    }
}
