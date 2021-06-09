#include "nchain.hpp"
#include "tnarr.hpp"

namespace wrd {

    WRD_DEF_ME(nchain)

    me::nchain(): _arr(new narr()) {}

    wcnt me::len() const {
        wcnt len = 0;
        /* TODO: container iterator
        for(auto& container : *this) {
            len += container.len();
        }*/

        return len;
    }

    wbool me::set(const iterator& at, const node& new1) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    wbool me::add(const iterator& at, const node& new1) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    wbool me::del(const iterator& at) {
        iterator& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    wcnt me::del(const iterator& from, const iterator& end) {
        iterator& fromInnerIter = _getContainerIterFromChainIter(from);
        ncontainer& fromCon = fromInnerIter.getContainer();
        iterator& endInnerIter = _getContainerIterFromChainIter(end);
        ncontainer& endCon = endInnerIter.getContainer();
        if(endInnerIter.isFrom(fromCon)) return fromCon.del(fromInnerIter, endInnerIter);

        wcnt ret = 0;
        /* TODO: container iterator:
        each<ncontainer>(from, nulOf<iterator>(), [&](me& chn, ncontainer& itsCon) {
            wbool isLast = false;
            iterator    head = &itsCon == &fromCon ? fromInnerIter : itsCon.begin(),
                    tail = &itsCon == &endCon ? isLast = true, endInnerIter : itsCon.end();
            ret += itsCon.del(head, tail);
            return !isLast;
        });*/

        return ret;
    }

    tstr<me> me::link(const ncontainer& new1) {
        if(nul(new1)) return tstr<me>();

        me& ret = new1.getType().isSub<me>() ? (me&) new1 : *new me(new1);
        link(ret);
        return tstr<me>(ret);
    }

    wbool me::link(const me& new1) {
        if(nul(new1) || nul(new1.getContainer())) return tstr<me>();
        if(&new1.getContainer() == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), tstr<me>();

        return _next.bind(new1);
    }

    wbool me::unlink() {
        return _next.unbind();
    }

    void me::empty() {
        _arr->empty();
        /* TODO: container iter:
        each<ncontainer>([](me& chn, ncontainer& itsCon) {
            itsCon.empty();
            return true;
        });*/
    }

    me& me::_getLastChain() {
        me* last = nullptr;
        /* TODO: container iter:
        each<ncontainer>([&last](me& chn, ncontainer& con) {
            last = &chn;
            return true;
        });*/
        return *last;
    }
}
