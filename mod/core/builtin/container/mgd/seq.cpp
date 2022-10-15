#include "seq.hpp"
#include "../../../visitor/visitInfo.hpp"
#include "../../../visitor/visitor.hpp"
#include "../../../bridge/cpp.hpp"

namespace namu {

    NAMU(DEF_ME(seq), DEF_VISIT())

    me::seq(nint start, nint end): super(new nseq(start, end)) {}
    me::seq(nint start, nint end, nint step): super(new nseq(start, end, step)) {}

    nbicontainer& me::subs() {
        nbicontainer& subs = super::subs();
        if(subs.len() <= 0) {
            func("len", &nseq::len);
        }

        return subs;
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        return get()._onMakeIteration(step);
    }
}
