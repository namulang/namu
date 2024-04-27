#pragma once

#include "verifier.hpp"

namespace namu {

#define ME verifier

    template <typename... Args>
    void ME::_warnMsg(Args... args) {
        _report(err::newWarn(args...));
    }
    template <typename... Args>
    void ME::_errMsg(Args... args) {
        _report(err::newErr(args...));
    }
    template <typename... Args>
    void ME::_infoMsg(Args... args) {
        _report(err::newInfo(args...));
    }

    template <typename... Args>
    void ME::_warn(const node& it, errCode code, Args... args) {
        _report(err::newWarn(it.getSrc().getPos(), code, args...));
    }
    template <typename... Args>
    void ME::_err(const node& it, errCode code, Args... args) {
        _report(err::newErr(it.getSrc().getPos(), code, args...));
    }
    template <typename... Args>
    void ME::_info(const node& it, errCode code, Args... args) {
        _report(err::newInfo(it.getSrc().getPos(), code, args...));
    }

#undef ME
}
