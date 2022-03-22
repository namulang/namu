#pragma once

#include "tnchain.hpp"
#include "tnarr.hpp"

namespace wrd {

#define TEMPL template <typename T, typename defaultContainer>
#define ME tnchain<T, defaultContainer>

    TEMPL
    ME::tnchain(): _arr(new defaultContainer()) {}

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
    wbool ME::set(const iter& at, const node& new1) {
        iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    TEMPL
    wbool ME::add(const iter& at, const node& new1) {
        iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    TEMPL
    wbool ME::del(const iter& at) {
        iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    TEMPL
    wcnt ME::del(const iter& from, const iter& end) {
        const me& fromChain = from.getContainer().template cast<me>();
        const me& endChain = end.getContainer().template cast<me>();

        me* e = (me*) &fromChain;
        wcnt ret = 0;
        do {
            tnucontainer<T>& eArr = e->getContainer();
            iter arrBegin = e == &fromChain ? _getArrIterFromChainIter(from) : eArr.begin(),
                 arrEnd = e == &endChain ? _getArrIterFromChainIter(end) : eArr.end();
            ret += eArr.del(arrBegin, arrEnd);
            e = &e->getNext();
        } while(e != &endChain);

        return ret;
    }

    TEMPL
    tstr<ME> ME::link(const tnucontainer<T>& new1) {
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
    ME* ME::wrap(const tnucontainer<T>& toShallowWrap) {
        ME* ret = const_cast<me*>(&toShallowWrap.template cast<ME>());
        if(nul(ret)) {
            ret = new me();
            ret->_arr.bind(toShallowWrap);
        }

        return ret;
    }

    TEMPL
    void ME::rel() {
        for(me* e=this; e ;e=&e->getNext())
            e->getContainer().rel();
    }

    TEMPL
    tnucontainer<T>& ME::getContainer() {
        return *_arr;
    }

#undef ME
#undef TEMPL
}
