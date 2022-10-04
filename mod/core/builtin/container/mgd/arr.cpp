#include "arr.hpp"
#include "../../../visitor/visitor.hpp"
#include "../../../visitor/generalizer.hpp"
#include "../../../bridge/cpp.hpp"

namespace namu {

    NAMU(DEF_ME(arr), DEF_VISIT())

    me::arr(): super(new narr()), _type(new obj()) {}
    me::arr(const node& newType): super(new narr()), _type(newType) {}

    node& me::operator[](nidx n) {
        return get()[n];
    }

    ncnt me::len() const {
        return get().len();
    }

    nbool me::has(nidx n) const {
        return get().has(n);
    }

    node& me::get(nidx n) {
        return get().get(n);
    }

    nbool me::set(const iter& at, const node& new1) {
        if(!new1.isSub(*_type)) return false;
        return get().set(at, new1);
    }
    nbool me::set(nidx n, const node& new1) {
        if(!new1.isSub(*_type)) return false;
        return get().set(n, new1);
    }

    nbool me::add(const iter& at, const node& new1) {
        if(!new1.isSub(*_type)) return false;
        return get().add(at, new1);
    }

    nbool me::add(nidx n, const node& new1) {
        if(!new1.isSub(*_type)) return false;
        return get().add(n, new1);
    }

    void me::add(const iter& here, const iter& from, const iter& to) {
        get().add(here, from, to);
    }

    //  del:
    nbool me::del(nidx n) {
        return get().del(n);
    }

    nbool me::del(const iter& it) {
        return get().del(it);
    }

    nbool me::del(const iter& from, const iter& to) {
        return get().del(from, to);
    }

    //  etc:
    me* me::deepClone() const {
        me* ret = clone();
        tstr<tnarr<node>> cloned = get().deepClone();
        ret->get().add(*cloned);
        return ret;
    }

    void me::rel() {
       get().rel();
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        return get()._onMakeIteration(step);
    }

    scope& me::_defGeneric(cache& c, const type* key) {
        tstr<scope> clone = _getOriginScope().deepClone();
        c.insert({key, clone}); // this avoids infinite loop.

        generalizer g;
        g.add(*new param(TYPENAME, *_type))
         .setRoot(*this)
         .start();

        return *clone;
    }

    scope& me::_getOriginScope() {
        static scope inner;
        if(inner.len() <= 0) {
            inner.add("len", this->func("len", &narr::len));
        }

        return inner;
    }
}
