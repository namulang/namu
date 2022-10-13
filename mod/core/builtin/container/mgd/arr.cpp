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
        str ased = new1.asImpli(*_type);
        if(!ased) return false;
        return get().set(at, *ased);
    }
    nbool me::set(nidx n, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;
        return get().set(n, *ased);
    }

    nbool me::add(const iter& at, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;

        return get().add(at, *ased);
    }

    nbool me::add(nidx n, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;

        return get().add(n, *ased);
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
    clonable* me::deepClone() const {
        me* ret = (me*) clone();
        tstr<tnarr<node>> cloned((tnarr<node>*) get().deepClone());
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
        static super* inner = nullptr;
        if(nul(inner)) {
            inner = new super();
            inner->genericFunc("len", &narr::len);
            inner->genericFunc("rel", &narr::rel);
            inner->genericFunc<nbool, nidx>("del", &narr::del);
            inner->genericFunc<nbool, const node&>("add", &narr::add);
            inner->genericFunc<nbool, nidx, const node&>("add", &narr::add);
            inner->genericFunc<nbool, nidx, const node&>("set", &narr::set);
            inner->genericFunc<node&, nidx>("get", &narr::get);
            inner->genericFunc("has", &narr::has);
        }

        return inner->subs().cast<scope>();
    }
}
