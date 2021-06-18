#pragma once

#include "tnchain.hpp"
#include "tnarr.hpp"

namespace wrd {

#define TEMPL template <typename T>
#define ME tnchain<T>

    TEMPL
    ME::tnchain(): _arr(new narr()) {}

    TEMPL
    wcnt ME::len() const {
        wcnt len = 0;

        for(chnIter e=beginChain(); e ;++e)
            len += e->getContainer().len();

        return len;
    }

    TEMPL
    wcnt ME::chainLen() const {
        wcnt len = 0;
        for(chnIter e = beginChain(); e ;++e)
            len++;

        return len;
    }

    TEMPL
    wbool ME::set(const wrd::iter& at, const node& new1) {
        wrd::iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    TEMPL
    wbool ME::add(const wrd::iter& at, const node& new1) {
        wrd::iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    TEMPL
    wbool ME::del(const wrd::iter& at) {
        wrd::iter& containerIter = _getArrIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    TEMPL
    wcnt ME::del(const wrd::iter& from, const wrd::iter& end) {
        const me& fromChain = from.getContainer().cast<me>();
        const me& endChain = end.getContainer().cast<me>();

        chnIter e = _iterChain(fromChain);
        wcnt ret = 0;
        do {
            me& eChain = *e;
            ncontainer& eArr = eChain.getContainer();
            wrd::iter   arrBegin = &eChain == &fromChain ? _getArrIterFromChainIter(from) : eArr.begin(),
                        arrEnd = &eChain == &endChain ? _getArrIterFromChainIter(end) : eArr.end();

            ret += eArr.del(arrBegin, arrEnd);
        } while(&(e++).get() != &endChain);

        return ret;
    }

    TEMPL
    tstr<ME> ME::link(const ncontainer& new1) {
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
        return _next.unbind();
    }

    TEMPL
    void ME::empty() {
        for(chnIter e=beginChain(); e ;++e)
            e->getContainer().empty();
    }

#undef ME
#undef TEMPL
}
