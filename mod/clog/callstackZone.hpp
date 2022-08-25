#pragma once

#include "logger.hpp"

namespace namu {

    struct callstackZone {
        callstackZone(nbool toShow) {
            logger& log = logger::get();
            prev = log.isShowCallstack();
            log.setCallstack(toShow);
        }
        ~callstackZone() {
            logger::get().setCallstack(prev);
        }

        nbool prev;
    };
}
