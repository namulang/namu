#include "seq.hpp"
#include "../../../visitor/visitInfo.hpp"
#include "../../../visitor/visitor.hpp"
#include "../../../bridge/cpp.hpp"

namespace namu {

    NAMU(DEF_ME(seq), DEF_VISIT())

    me::seq(nint start, nint end): super(new nseq(start, end)) {}
    me::seq(nint start, nint end, nint step): super(new nseq(start, end, step)) {}

    nbicontainer& me::subs() {
        static super* inner;
        if(nul(inner)) {
            inner = new super();
            inner->func("len", &nseq::len);
            inner->func("get", &nseq::get);
            inner->func("has", &nseq::has);
        }

        return inner->subs();
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        return get()._onMakeIteration(step);
    }
}
