#pragma once

#include "verification.hpp"
#include "verifier.hpp"

namespace wrd {

#define ME verification 

    template <typename ErrT, typename... Args>
    wbool ME::_warn(Args... args) {
        _getVerifier().getReport().add(new ErrT(err::WARN, args...));
        return false;
    }
    template <typename ErrT, typename... Args>
    wbool ME::_err(Args... args) {
        _getVerifier().getReport().add(new ErrT(err::ERR, args...));
        return true;
    }
    template <typename ErrT, typename... Args>
    wbool ME::_info(Args... args) {
        _getVerifier().getReport().add(new ErrT(err::INFO, args...));
        return false;
    }

#undef ME
}
