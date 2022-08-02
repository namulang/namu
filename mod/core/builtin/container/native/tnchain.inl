#pragma once

#include "tnchain.hpp"
#include "tnmap.inl"

namespace namu {

#define TEMPL template <typename K, typename V, typename defaultContainer>
#define ME tnchain<K, V, defaultContainer>

    TEMPL
    ME::tnchain(): _map(new defaultContainer()) {}

    TEMPL
    wbool ME::has(const K& key) const {
        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            if(e->getContainer().has(key))
                return true;
        return false;
    }

    TEMPL
    wcnt ME::len() const {
        wcnt len = 0;

        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            len += e->getContainer().len();
        return len;
    }

    TEMPL
    wcnt ME::chainLen() const {
        wcnt len = 0;
        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            len++;

        return len;
    }

    TEMPL
    V& ME::get(const K& key) {
        for(tstr<me> e(this); e ;e.bind(e->getNext())) {
            V& got = e->getContainer().get(key);
            if(!nul(got))
                return got;
        }

        return nulOf<V>();
    }

    TEMPL
    void ME::_getAll(const K& key, narr& tray) const {
        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            e->getContainer()._getAll(key, tray);
    }

    TEMPL
    wbool ME::add(const K& key, const V& new1) {
        return getContainer().add(key, new1);
    }

    TEMPL
    wbool ME::del(const K& key) {
        wbool ret = true;
        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            if(e->has(key))
                ret = e->getContainer().del(key) ? ret : false;
        return ret;
    }

    TEMPL
    wbool ME::del(const iter& at) {
        const me& owner = at.getContainer().template cast<me>();

        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            if(&e.get() == &owner)
                return e->getContainer().del(_getMapIterFromChainIter(at));
        return false;
    }

    TEMPL
    wbool ME::del(const iter& from, const iter& last) {
        const me* fromChain = &from.getContainer().template cast<me>();
        const me* lastChain = &last.getContainer().template cast<me>();
        if(nul(lastChain)) return WRD_W("iterator 'end' owned by null chain instance."), false;
        const me* endChain = &lastChain->getNext(); // now, endChain can be null but it's okay.

        me* e = (me*) fromChain;
        wbool ret = true;
        do {
            super& eArr = e->getContainer();
            iter arrBegin = e == fromChain ? _getMapIterFromChainIter(from) : eArr.begin(),
                 arrLast = e == lastChain ? _getMapIterFromChainIter(last) : eArr.end();
            ret = eArr.del(arrBegin, arrLast) ? ret : false;
            e = &e->getNext();
        } while(e != endChain);

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
        for(tstr<me> e(this); e ;e.bind(e->getNext()))
            e->getContainer().rel();
    }

    TEMPL
    tnbicontainer<K, V>& ME::getContainer() {
        return *_map;
    }

#undef ME
#undef TEMPL
}
