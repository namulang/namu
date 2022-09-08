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
    void ME::_srcWarn(const point& pos, Args... args) {
        getReport().add(err::newWarn(pos, args...));
        _leaveErrFrame();
    }
    template <typename... Args>
    void ME::_srcErr(const point& pos, Args... args) {
        getReport().add(err::newErr(pos, args...));
        _leaveErrFrame();
        NAMU_CALLSTACK();
    }
    template <typename... Args>
    void ME::_srcInfo(const point& pos, Args... args) {
        getReport().add(err::newInfo(pos, args...));
    }

#undef ME
}
