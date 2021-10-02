#pragma once

#include "err.hpp"

namespace wrd {

    class errReport : public std::vector<err>, typeProvidable, clonable {
        WRD(CLASS(errReport, std::vector<err>))

    public:
        wbool hasErr() const {
            return has(err::ERR);
        }
        wbool hasWarn() const {
            return has(err::WARN);
        }
        wbool has(err::type type) const {
            // TODO:
            return false;
        }
    };
}

