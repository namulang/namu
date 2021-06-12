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
    wbool ME::set(const wrd::iter& at, const node& new1) {
        wrd::iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    TEMPL
    wbool ME::add(const wrd::iter& at, const node& new1) {
        wrd::iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    TEMPL
    wbool ME::del(const wrd::iter& at) {
        wrd::iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    TEMPL
    wcnt ME::del(const wrd::iter& from, const wrd::iter& end) {
        wrd::iter& fromInnerIter = _getContainerIterFromChainIter(from);
        ncontainer& fromCon = fromInnerIter.getContainer();
        wrd::iter& endInnerIter = _getContainerIterFromChainIter(end);
        ncontainer& endCon = endInnerIter.getContainer();
        if(endInnerIter.isFrom(fromCon)) return fromCon.del(fromInnerIter, endInnerIter);

        wcnt ret = 0;
        /* TODO: container wrd::iter:
        each<ncontainer>(from, nulOf<wrd::iter>(), [&](ME& chn, ncontainer& itsCon) {
            wbool isLast = false;
            wrd::iter    head = &itsCon == &fromCon ? fromInnerIter : itsCon.begin(),
                        tail = &itsCon == &endCon ? isLast = true, endInnerIter : itsCon.end();
            ret += itsCon.del(head, tail);
            return !isLast;
        });*/

        return ret;
    }

    TEMPL
    tstr<ME> ME::link(const ncontainer& new1) {
        if(nul(new1)) return tstr<ME>();

        ME& ret = new1.getType().isSub<ME>() ? (ME&) new1 : *new ME(new1);
        link(ret);
        return tstr<ME>(ret);
    }

    TEMPL
    wbool ME::link(const ME& new1) {
        if(nul(new1) || nul(new1.getContainer())) return tstr<ME>();
        if(&new1.getContainer() == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), tstr<ME>();

        return _next.bind(new1);
    }

    TEMPL
    wbool ME::unlink() {
        return _next.unbind();
    }

    TEMPL
    void ME::empty() {
        _arr->empty();
        /* TODO: container wrd::iter:
        each<ncontainer>([](ME& chn, ncontainer& itsCon) {
            itsCon.empty();
            return true;
        });*/
    }

#undef ME
#undef TEMPL
}
