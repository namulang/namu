#pragma once

#include "verifier.hpp"

namespace namu {

#define ME verifier

    template <typename... Args>
    void ME::_warn(Args... args) {
        getReport().add(err::newWarn(args...));
        _leaveErrFrame();
    }
    template <typename... Args>
    void ME::_err(Args... args) {
        getReport().add(err::newErr(args...));
        _leaveErrFrame();
        NAMU_CALLSTACK();
    }
    template <typename... Args>
    void ME::_info(Args... args) {
        getReport().add(err::newInfo(args...));
    }

    template <typename... Args>
    void ME::_warn(const point& pos, errCode code, Args... args) {
        getReport().add(err::newWarn(pos, code, args...));
        _leaveErrFrame();
    }
    template <typename... Args>
    void ME::_err(const point& pos, errCode code, Args... args) {
        getReport().add(err::newErr(pos, code, args...));
        _leaveErrFrame();
        NAMU_CALLSTACK();
    }
    template <typename... Args>
    void ME::_info(const point& pos, errCode code, Args... args) {
        getReport().add(err::newInfo(pos, code, args...));
    }

#undef ME
}
