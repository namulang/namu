#pragma once

#include "verifier.hpp"

namespace namu {

#define ME verifier

    template <typename... Args>
    void ME::_warn(Args... args) {
        _report(err::newWarn(args...));
    }
    template <typename... Args>
    void ME::_err(Args... args) {
        _report(err::newErr(args...));
    }
    template <typename... Args>
    void ME::_info(Args... args) {
        _report(err::newInfo(args...));
    }

    template <typename... Args>
    void ME::_warn(const point& pos, errCode code, Args... args) {
        _report(err::newWarn(pos, code, args...));
    }
    template <typename... Args>
    void ME::_warn(const node& it, errCode code, Args... args) {
        _report(err::newWarn(it.getSrc().getPos(), code, args...));
    }
    template <typename... Args>
    void ME::_err(const point& pos, errCode code, Args... args) {
        _report(err::newErr(pos, code, args...));
    }
    template <typename... Args>
    void ME::_err(const node& it, errCode code, Args... args) {
        _report(err::newErr(it.getSrc().getPos(), code, args...));
    }
    template <typename... Args>
    void ME::_info(const point& pos, errCode code, Args... args) {
        _report(err::newInfo(pos, code, args...));
    }
    template <typename... Args>
    void ME::_info(const node& it, errCode code, Args... args) {
        _report(err::newInfo(it.getSrc().getPos(), code, args...));
    }

#undef ME
}
