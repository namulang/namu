#include "callstackZone.hpp"

NAMU(DEF_ME(callstackZone)

namespace namu {
    me::callstackZone(nbool toShow) {
        logger& log = logger::get();
        prev = log.isShowCallstack();
        log.setCallstack(toShow);
    }

    me::~callstackZone() {
        logger::get().setCallstack(prev);
    }
}
