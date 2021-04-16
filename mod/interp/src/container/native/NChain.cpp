#include "NContainer.inl"
#include "NChain.hpp"
#include "NArr.hpp"

namespace wrd {

    WRD_DEF_ME(NChain)

    me::NChain(): _arr(new NArr()) {}

    wcnt me::getLen() const {
        wcnt len = 0;
        each<NContainer>([&len](const me& chn, const NContainer& con) {
            len += con.getLen();
            return true;
        });

        return len;
    }

    wbool me::set(const Iter& at, const Node& new1) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    wbool me::add(const Iter& at, const Node& new1) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    wbool me::add(const Node& new1) {
        return getContainer().add(new1);
    }

    wbool me::del() {
        NChain& last = _getLastChain();
        if(nul(last)) return false;

        return last.getContainer().del();
    }

    wbool me::del(const Node& it) {
        wbool ret = false;
        each<Node>([&ret, &it](const Iter& e, Node& elem) {
            if(&elem != &it) return true;

            ret = const_cast<NContainer&>(e.getContainer()).del(e);
            return false;
        });

        return ret;
    }

    wbool me::del(const Iter& at) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    wcnt me::del(const Iter& from, const Iter& end) {
        Iter& fromInnerIter = _getContainerIterFromChainIter(from);
        NContainer& fromCon = fromInnerIter.getContainer();
        Iter& endInnerIter = _getContainerIterFromChainIter(end);
        NContainer& endCon = endInnerIter.getContainer();
        if(endInnerIter.isFrom(fromCon)) return fromCon.del(fromInnerIter, endInnerIter);

        wcnt ret = 0;
        each<NContainer>(from, nulOf<Iter>(), [&](NChain& chn, NContainer& itsCon) {
            wbool isLast = false;
            Iter    head = &itsCon == &fromCon ? fromInnerIter : itsCon.head(),
                    tail = &itsCon == &endCon ? isLast = true, endInnerIter : itsCon.tail();
            ret += itsCon.del(head, tail);
            return !isLast;
        });

        return ret;
    }

    TStr<NChain> me::link(const NContainer& new1) {
        NChain* ret = new NChain(new1);
        link(*ret);
        return TStr<NChain>(ret);
    }

    wbool me::link(const NChain& new1) {
        if(nul(new1) || nul(new1.getContainer())) return TStr<NChain>();
        if(&new1.getContainer() == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), TStr<NChain>();

        return _next.bind(new1);
    }

    wbool me::unlink() {
        return _next.unbind();
    }

    Iter me::head() const {
        return Iter(new NChainIteration(*this, *this, _arr->head()));
    }

    Iter me::iter(wcnt step) const {
        Iter ret = head();
        ret.next(step);
        return ret;
    }

    Iter me::tail() const {
        const NChain& last = _getLastChain();
        if(nul(last)) return Iter();

        return Iter(new NChainIteration(*this, last, last._arr->tail()));
    }

    Iter me::last() const {
        const NChain& last = _getLastChain();
        if(nul(last)) return Iter();

        return Iter(new NChainIteration(*this, last, last._arr->last()));
    }

    void me::empty() {
        _arr->empty();
        each<NContainer>([](NChain& chn, NContainer& itsCon) {
            itsCon.empty();
            return true;
        });
    }

    NChain& me::_getLastChain() {
        NChain* last = nullptr;
        each<NContainer>([&last](NChain& chn, NContainer& con) {
            last = &chn;
            return true;
        });
        return *last;
    }

}
