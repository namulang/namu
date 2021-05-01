#include "ncontainer.inl"
#include "narr.hpp"

namespace wrd {

    WRD_DEF_ME(narr)

    node& me::get(widx n) {
        if(!_isValidN(n)) return nulOf<node>();

        binder& ret = _vec[n];
        return (node&) *ret;
    }

    wbool me::set(const iterator& at, const node& new1) {
        narrIteration& cast = _getIterationFrom(at);
        if(nul(cast)) return false;
        if(cast.isEnd()) return false;

        return set(cast._n, new1);
    }

    wbool me::_isValidN(widx n) const {
        return 0 <= n && n < len();
    }

    wbool me::set(widx n, const node& new1) {
        if(!_isValidN(n)) return false;

        _vec[n].bind(new1);
        return true;
    }

    wbool me::add(const iterator& e, const node& new1) {
        if(nul(e) || nul(new1)) return false;
        if(!e.isFrom(*this)) return false;
        narrIteration& cast = (narrIteration&) *e._step;
        if(nul(cast)) return false;

        return add(cast._n, new1);
    }

    wbool me::add(widx n, const node& new1) {
        if(n < 0 || n > len()) return false; // if n equals to len(), it means that will be added at end of container.

        str wrap(new1);
        if(!wrap) return false;
        _vec.insert(_vec.begin() + n, str(new1));
        return true;
    }

    wbool me::del() {
        return del(iter(len() - 1));
    }

    wbool me::del(const iterator& at) {
        narrIteration& cast = _getIterationFrom(at);
        if(nul(cast)) return false;
        if(cast.isEnd()) return false;

        return del(cast._n);
    }

    wbool me::del(widx n) {
        if(!_isValidN(n)) return false;
        _vec.erase(_vec.begin() + n);
        return true;
    }

    wcnt me::del(const iterator& from, const iterator& end) {
        narrIteration&  endIter = _getIterationFrom(end),
                    &   fromIter = _getIterationFrom(from);
        if(nul(endIter) || nul(fromIter))
            return WRD_E("from(%x) or end(%x) one of these is null.", &endIter, &fromIter), 0;

        widx fromN = fromIter.isEnd() ? len()-1 : fromIter._n;
        wcnt cnt = endIter._n - fromN;
        if(cnt <= 0) return 0;

        for(int n=0; n < cnt ;n++)
            _vec.erase(_vec.begin() + fromN);
        return cnt;
    }


    wcnt me::len() const {
        return _vec.size();
    };

    void me::empty() {
        _vec.clear();
    }

    tstr<instance> me::deepClone() const {
        me* ret = new me();
        for(auto e=begin(); e ;e++)
            ret->add((node*) e->clone());

        return tstr<instance>(ret);
    }
}
