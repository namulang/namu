#include "../tucontainable.inl"
#include "nseq.hpp"

namespace namu {

    NAMU(DEF_ME(nseq))

    ncnt me::len() const {
        return abs(_end - _start);
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        me* unconst = const_cast<me*>(this);
        return new nseqIteration(*unconst, step);
    }

    nint& me::get(nidx n) {
        static nint inner;
        if(n >= len()) n = len() - 1;
        if(n < 0) n = 0;

        return inner = _start + _step * n;
    }

    nbool me::has(nidx n) const {
        return len() > n && n >= 0;
    }
}
