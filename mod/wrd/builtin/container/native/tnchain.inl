#pragma once

#include "tnchain.hpp"
#include "tnarr.hpp"

namespace wrd {

#define TEMPL template <typename T, typename defaultContainer>
#define ME tnchain<T, defaultContainer>

    TEMPL
    ME::tnchain(): _map(new defaultContainer()) {}

    TEMPL
    wcnt ME::len() const {
        wcnt len = 0;

        for(const me* e=this; e ;e=&e->getNext())
            len += e->getContainer().len();
        return len;
    }

    TEMPL
    wcnt ME::chainLen() const {
        wcnt len = 0;
        for(const me* e=this; e ;e=&e->getNext())
            len++;

        return len;
    }

    TEMPL
    wbool ME::set(const K& key, const V& new1) {
        for(me* e=this; e ;e=&e->getNext())
            if(e->has(key))
                return e->getContainer().set(key, new1);
        return false;
    }

    TEMPL
    wbool ME::add(const K& key, const V& new1) {
        return getContainer().add(key, new1);
    }

    TEMPL
    wbool ME::del(const K& key) {
        for(me* e=this; e ;e=&e->getNext())
            if(e->has(key))
                return e->getContainer().del(key);
        return false;
    }

    TEMPL
    wcnt ME::del(const iter& from, const iter& end) {
        const me& fromChain = from.getContainer().template cast<me>();
        const me& endChain = end.getContainer().template cast<me>();

        me* e = (me*) &fromChain;
        wcnt ret = 0;
        do {
            super& eArr = e->getContainer();
            iter arrBegin = e == &fromChain ? _getMapIterFromChainIter(from) : eArr.begin(),
                 arrEnd = e == &endChain ? _getMapIterFromChainIter(end) : eArr.end();
            ret += eArr.del(arrBegin, arrEnd);
            e = &e->getNext();
        } while(e != &endChain);

        return ret;
    }

    TEMPL
    tstr<ME> ME::link(const super& new1) {
        if(nul(new1)) return tstr<ME>();

        ME& ret = *wrap(new1);
        link(ret);
        return tstr<ME>(ret);
    }

    TEMPL
    wbool ME::link(const ME& new1) {
        if(nul(new1) || nul(new1.getContainer())) return false;
        if(&new1.getContainer() == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), false;

        return _next.bind(new1);
    }

    TEMPL
    wbool ME::unlink() {
        _next.rel();
		return true;
    }

    TEMPL
    ME* ME::wrap(const super& toShallowWrap) {
        ME* ret = const_cast<me*>(&toShallowWrap.template cast<ME>());
        if(nul(ret)) {
            ret = new me();
            ret->_map.bind(toShallowWrap);
        }

        return ret;
    }

    TEMPL
    void ME::rel() {
        for(me* e=this; e ;e=&e->getNext())
            e->getContainer().rel();
    }

    TEMPL
    tnbicontainer<T>& ME::getContainer() {
        return *_map;
    }

#undef ME
#undef TEMPL
}
