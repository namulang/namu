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
        /* TODO: container iterator
        for(auto& container : *this) {
            len += container.len();
        }*/

        return len;
    }

    TEMPL
    wbool ME::set(const iterator& at, const node& new1) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    TEMPL
    wbool ME::add(const iterator& at, const node& new1) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    TEMPL
    wbool ME::del(const iterator& at) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    TEMPL
    wcnt ME::del(const iterator& from, const iterator& end) {
        iterator& fromInnerIter = _getContainerIterFromChainIter(from);
        ncontainer& fromCon = fromInnerIter.getContainer();
        iterator& endInnerIter = _getContainerIterFromChainIter(end);
        ncontainer& endCon = endInnerIter.getContainer();
        if(endInnerIter.isFrom(fromCon)) return fromCon.del(fromInnerIter, endInnerIter);

        wcnt ret = 0;
        /* TODO: container iterator:
        each<ncontainer>(from, nulOf<iterator>(), [&](ME& chn, ncontainer& itsCon) {
            wbool isLast = false;
            iterator    head = &itsCon == &fromCon ? fromInnerIter : itsCon.begin(),
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
        /* TODO: container iter:
        each<ncontainer>([](ME& chn, ncontainer& itsCon) {
            itsCon.empty();
            return true;
        });*/
    }

    TEMPL
    ME& ME::_getLastChain() {
        ME* last = nullptr;
        /* TODO: container iter:
        each<ncontainer>([&last](ME& chn, ncontainer& con) {
            last = &chn;
            return true;
        });*/
        return *last;
    }

#undef ME
#undef TEMPL
}
