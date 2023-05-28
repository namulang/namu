#include "callstackZone.hpp"

namespace namu {

    NAMU(DEF_ME(callstackZone))

    me::callstackZone(nbool toShow) {
        logger& log = logger::get();
        prev = log.isShowCallstack();
        log.setCallstack(toShow);
    }

    me::~callstackZone() {
        logger::get().setCallstack(prev);
    }
}
