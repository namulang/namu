#pragma once

#include "common.hpp"

namespace namu {
    class logLv {
        NAMU(ME(logLv))

    public:
        enum level {
            ERR,
            WARN,
            INFO
        };

    public:
        static const std::string& getName(level lv);
    };
}
