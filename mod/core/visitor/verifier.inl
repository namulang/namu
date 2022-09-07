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
    void ME::_srcWarn(Args... args) {
        getReport().add(err::newWarn(_getIt().getPos(), args...));
        _leaveErrFrame();
    }
    template <typename... Args>
    void ME::_srcErr(Args... args) {
        getReport().add(err::newErr(_getIt().getPos(), args...));
        _leaveErrFrame();
        NAMU_CALLSTACK();
    }
    template <typename... Args>
    void ME::_srcInfo(Args... args) {
        getReport().add(err::newInfo(_getIt().getPos(), args...));
    }

#undef ME
}
