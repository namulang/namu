#pragma once

#include "verification.hpp"
#include "verifier.hpp"

namespace wrd {

#define ME verification

    template <typename... Args>
    void ME::_warn(Args... args) {
        _getVerifier().getReport().add(err::newWarn(args...));
    }
    template <typename... Args>
    void ME::_err(Args... args) {
        _getVerifier().getReport().add(err::newErr(args...));
    }
    template <typename... Args>
    void ME::_info(Args... args) {
        _getVerifier().getReport().add(err::newInfo(args...));
    }

#undef ME
}
