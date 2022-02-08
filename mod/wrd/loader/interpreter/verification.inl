#pragma once

#include "verification.hpp"
#include "verifier.hpp"

namespace wrd {

#define ME verification 

    template <typename... Args>
    wbool ME::_warn(Args... args) {
        _getVerifier().getReport().add(err::newWarn(args...));
        return false;
    }
    template <typename... Args>
    wbool ME::_err(Args... args) {
        _getVerifier().getReport().add(err::newErr(args...));
        return true;
    }
    template <typename... Args>
    wbool ME::_info(Args... args) {
        _getVerifier().getReport().add(err::newInfo(args...));
        return false;
    }

#undef ME
}
