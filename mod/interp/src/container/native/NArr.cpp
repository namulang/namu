#include "NContainer.inl"
#include "NArr.hpp"

namespace wrd {

    WRD_DEF_THIS(NArr)

    Node& This::get(widx n) {
        if(!_isValidN(n)) return nulOf<Node>();

        Bind& ret = _vec[n];
        return (Node&) *ret;
    }

    wbool This::set(const Iter& at, const Node& new1) {
        NArrIteration& cast = _getIterationFrom(at);
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
        if(nul(cast)) return false;

        return add(cast._n, new1);
    }

    wbool This::add(widx n, const Node& new1) {
        if(n < 0 || n > getLen()) return false; // if n equals to getLen(), it means that will be added at end of container.

        Str wrap(new1);
        if(!wrap) return false;
        _vec.insert(_vec.begin() + n, Str(new1));
        return true;
    }

    wbool This::del(const Iter& at) {
        NArrIteration& cast = _getIterationFrom(at);
        if(nul(cast)) return false;

        _vec.erase(_vec.begin() + cast._n);
        return del(cast._n);
    }

    wbool This::del(widx n) {
        if(!_isValidN(n)) return false;
        _vec.erase(_vec.begin() + n);
        return true;
    }

    wcnt This::del(const Iter& from, const Iter& end) {
        NArrIteration&  endIter = _getIterationFrom(end),
                    &   fromIter = _getIterationFrom(from);
        if(nul(endIter) || nul(fromIter))
            return WRD_E("from(%x) or end(%x) one of these is null.", &endIter, &fromIter), 0;

        widx fromN = fromIter._n;
        wcnt cnt = endIter._n - fromN;
        for(int n=0; n < cnt ;n++)
            _vec.erase(_vec.begin() + fromN);
        return cnt;
    }


    wcnt This::getLen() const {
        return _vec.size();
    };

    void This::empty() {
        _vec.clear();
    }
}
