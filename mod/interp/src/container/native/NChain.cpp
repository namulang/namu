#include "NContainer.inl"
#include "NChain.hpp"
#include "NArr.hpp"

namespace wrd {

    WRD_DEF_THIS(NChain)

    This::NChain(): _arr(new NArr()) {}

    wcnt This::getLen() const {
        wcnt len = 0;
        each<NContainer>([&len](const This& chn, const NContainer& con) {
            len += con.getLen();
            return true;
        });

        return len;
    }

    wbool This::set(const Iter& at, const Node& new1) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().set(containerIter, new1);
    }

    wbool This::add(const Iter& at, const Node& new1) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().add(containerIter, new1);
    }

    wbool This::add(const Node& new1) {
        return getContainer().add(new1);
    }

    wbool This::del() {
        NChain& last = _getLastChain();
        if(nul(last)) return false;

        return last.getContainer().del();
    }

    wbool This::del(const Node& it) {
        wbool ret = false;
        each<Node>([&ret, &it](Iter& e, Node& elem) {
            if(&elem != &it) return true;

            ret = e.getContainer().del(e);
            return false;
        });

        return ret;
    }

    wbool This::del(const Iter& at) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    wcnt This::del(const Iter& from, const Iter& end) {
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

    wbool This::link(const NContainer& new1) {
        if(&new1 == &getContainer())
            return WRD_W("recursive link detected!! new1(%x) is chain(%x)'s container.", &new1, &getContainer()), false;

        return _next.bind(new NChain(new1));
    }

    wbool This::link(const NChain& new1) {
        if(&new1 == this)
            return WRD_W("recursive link detected!! new1(%x) is thisptr.", &new1), false;

        return _next.bind(new1);
    }

    wbool This::unlink() {
        return _next.unbind();
    }

    Iter This::head() const {
        return Iter(new NChainIteration(*this, *this, _arr->head()));
    }

    Iter This::iter(wcnt step) const {
        Iter ret = head();
        ret.step(step);
        return ret;
    }

    Iter This::tail() const {
        const NChain& last = _getLastChain();
        if(nul(last)) return Iter();

        return Iter(new NChainIteration(*this, last, last._arr->tail()));
    }

    void This::empty() {
        _arr->empty();
        each<NContainer>([](NChain& chn, NContainer& itsCon) {
            itsCon.empty();
            return true;
        });
    }

    NChain& This::_getLastChain() {
        NChain* last = nullptr;
        each<NContainer>([&last](NChain& chn, NContainer& con) {
            last = &chn;
            return true;
        });
        return *last;
    }

}
