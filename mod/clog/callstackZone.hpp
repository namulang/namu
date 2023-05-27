#pragma once

#include "logger.hpp"

namespace namu {

    struct callstackZone {
        callstackZone(nbool toShow);
        ~callstackZone();

        nbool prev;
    };
}
