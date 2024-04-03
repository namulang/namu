#pragma once

#include "filterable.hpp"

namespace namu {
    class _nout errPassFilter : public filterable {
        NAMU(ME(errPassFilter, filterable))

    public:
        std::string filt(logLv::level lv, const nchar* tag, const std::string& msg) const override;
    };
}
