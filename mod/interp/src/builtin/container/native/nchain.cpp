#include "ncontainer.inl"
#include "nchain.hpp"
#include "narr.hpp"

namespace wrd {

    WRD_DEF_ME(nchain)

    me::nchain(): _arr(new narr()) {}

    wcnt me::len() const {
        wcnt len = 0;
        each<ncontainer>([&len](const me& chn, const ncontainer& con) {
            len += con.len();
            return true;
        });

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

    wbool me::add(const node& new1) {
        return getContainer().add(new1);
    }

    wbool me::del() {
        nchain& last = _getLastChain();
        if(nul(last)) return false;

        return last.getContainer().del();
    }

    wbool me::del(const node& it) {
        wbool ret = false;
        each<node>([&ret, &it](const iterator& e, node& elem) {
            if(&elem != &it) return true;

            ret = const_cast<ncontainer&>(e.getContainer()).del(e);
            return false;
        });

        return ret;
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
        each<ncontainer>(from, nulOf<iterator>(), [&](nchain& chn, ncontainer& itsCon) {
            wbool isLast = false;
            iterator    head = &itsCon == &fromCon ? fromInnerIter : itsCon.begin(),
                    tail = &itsCon == &endCon ? isLast = true, endInnerIter : itsCon.end();
            ret += itsCon.del(head, tail);
            return !isLast;
        });

        return ret;
    }

    tstr<nchain> me::link(const ncontainer& new1) {
        if(nul(new1)) return tstr<nchain>();

        nchain& ret = new1.getType().isSub<nchain>() ? (nchain&) new1 : *new nchain(new1);
        link(ret);
        return tstr<nchain>(ret);
    }

    wbool me::link(const nchain& new1) {
        if(nul(new1) || nul(new1.getContainer())) return tstr<nchain>();
        if(&new1.getContainer() == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), tstr<nchain>();

        return _next.bind(new1);
    }

    wbool me::unlink() {
        return _next.unbind();
    }

    iterator me::begin() const {
        return iterator(new nchainIteration(*this, *this, _arr->begin()));
    }

    iterator me::iter(wcnt step) const {
        iterator ret = begin();
        ret.next(step);
        return ret;
    }

    iterator me::end() const {
        const nchain& last = _getLastChain();
        if(nul(last)) return iterator();

        return iterator(new nchainIteration(*this, last, last._arr->end()));
    }

    iterator me::last() const {
        const nchain& last = _getLastChain();
        if(nul(last)) return iterator();

        return iterator(new nchainIteration(*this, last, last._arr->last()));
    }

    void me::empty() {
        _arr->empty();
        each<ncontainer>([](nchain& chn, ncontainer& itsCon) {
            itsCon.empty();
            return true;
        });
    }

    nchain& me::_getLastChain() {
        nchain* last = nullptr;
        each<ncontainer>([&last](nchain& chn, ncontainer& con) {
            last = &chn;
            return true;
        });
        return *last;
    }

}
