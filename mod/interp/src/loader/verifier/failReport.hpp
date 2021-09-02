#pragma once

#include "fail.hpp"

namespace wrd {

    class failReport : public std::vector<fail>, typeProvidable, clonable {
        WRD(CLASS(failReport, std::vector<fail>))

    public:
        wbool hasErr() const {
            return has(fail::ERR);
        }
        wbool hasWarn() const {
            return has(fail::WARN);
        }
        wbool has(fail::type type) const {
            // TODO:
            return false;
        }
    };
}

