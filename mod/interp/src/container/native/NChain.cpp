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

        return containerIter.getContainer().set(containerIter, new1);
    }

    wbool This::del(const Iter& at) {
        Iter& containerIter = _getContainerIterFromChainIter(at);

        return containerIter.getContainer().del(containerIter);
    }

    wbool This::link(const NContainer& new1) {
        return _next.bind(new NChain(new1));
    }

    wbool This::link(const NChain& new1) {
        return _next.bind(new1);
    }

    wbool This::unlink() {
        return _next.unbind();
    }

    Iter This::head() const {
        return Iter(new NChainIteration(*this, *this, _arr->head()));
    }

    Iter This::tail() const {
        const NChain* last = nullptr;
        each<NContainer>([&last](const NChain& chn, const NContainer& con) {
            last = &chn;
            return true;
        });

        if(!last) return Iter();

        return Iter(new NChainIteration(*this, *last, last->tail()));
    }

    void This::empty() {
        if(!_arr) return;

        _arr->empty();
    }
}
