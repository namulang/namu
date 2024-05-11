#include "../ast/node.hpp"
#include "err.hpp"
#include "../frame/frame.hpp"
#include "../frame/thread.hpp"

namespace namu {

    NAMU_DEF_ME(err)

    namespace {
        constexpr nint MAX_BUF = 512;
    }

    const std::string& err::getErrMsg(errCode code) {
        static std::string msg[] = {
            "start",
#define PAIRX PAIRX_RIGHT
#include "errCode.inl"
#undef PAIRX
            "end",
        };

        if(code < ERR_CODE_START) code = ERR_CODE_START;
        if(code > ERR_CODE_END) code = ERR_CODE_END;

        return msg[code];
    }

    const std::string& err::getErrName(errCode code) {
        static std::string msg[] = {
            "ERR_CODE_START",
#define PAIRX(A, B) #A,
#include "errCode.inl"
#undef PAIRX
            "ERR_CODE_END",
        };

        if(code < ERR_CODE_START) code = ERR_CODE_START;
        if(code > ERR_CODE_END) code = ERR_CODE_END;

        return msg[code];
    }

#define _EXPAND_VA(EXPR) \
        va_list args; \
        va_start(args, code); \
        err* ret = EXPR; \
        va_end(args); \
        return ret

    err* me::newErr(int code, ...) {
        _EXPAND_VA(new err(logLv::ERR, code, args));
    }
    err* me::newErr(const point& pos, int code, ...) {
        _EXPAND_VA(new err(logLv::ERR, pos, code, args));
    }
    err* me::newWarn(int code, ...) {
        _EXPAND_VA(new err(logLv::WARN, code, args));
    }
    err* me::newWarn(const point& pos, int code, ...) {
        _EXPAND_VA(new err(logLv::WARN, pos, code, args));
    }
    err* me::newInfo(int code, ...) {
        _EXPAND_VA(new err(logLv::INFO, code, args));
    }
    err* me::newInfo(const point& pos, int code, ...) {
        _EXPAND_VA(new err(logLv::INFO, pos, code, args));
    }

#undef _EXPAND_VA

    me::err(logLv::level t, nint newCode): super(), fType(t), code((errCode) newCode) {
        _stack.setStack(thread::get().getFrames());
    }

    me::err(logLv::level t, nint newCode, va_list args): super(), fType(t), code((errCode) newCode) {
        msg = _format(getErrMsg(code), args);
        _stack.setStack(thread::get().getFrames());
    }

    me::err(logLv::level t, const point& ps, nint newCode, va_list args)
        : super(), fType(t), code((errCode) newCode), pos(ps) {
        msg = _format(getErrMsg(code), args);
        _stack.setStack(thread::get().getFrames());
    }

    nbool me::operator==(const me& rhs) const {
        return fType == rhs.fType && code == rhs.code && code == rhs.code;
    }
    nbool me::operator!=(const me& rhs) const {
        return !operator==(rhs);
    }

    void me::log() const {
        using platformAPI::foreColor;
        auto& log = logger::get();
        switch(fType) {
            case logLv::ERR:
                if(pos.isOrigin())
                    log.logFormatBypass("%serr%d(%s)", foreColor(LIGHTRED).c_str(), code, getErrName(code).c_str());
                else
                    log.logFormatBypass("%serr%d(%s) %d:%d", foreColor(LIGHTRED).c_str(), code, getErrName(code).c_str(), pos.row, pos.col);
                break;

            case logLv::WARN:
                if(pos.isOrigin())
                    log.logFormatBypass("%swarn%d(%s)", foreColor(YELLOW).c_str(), code, getErrName(code).c_str());
                else
                    log.logFormatBypass("%swarn%d(%s) %d:%d", foreColor(YELLOW).c_str(), code, getErrName(code).c_str(), pos.row, pos.col);
                break;

            case logLv::INFO:
                if(pos.isOrigin())
                    log.logFormatBypass("%sinfo%d(%s)", foreColor(BLUE).c_str(), code, getErrName(code).c_str());
                else
                    log.logFormatBypass("%sinfo%d(%s) %d:%d", foreColor(BLUE).c_str(), code, getErrName(code).c_str(), pos.row, pos.col);
                break;
        }
        log.logFormatBypass("%s: %s\n", foreColor(LIGHTGRAY).c_str(), msg.c_str());
    }

    void me::dbgLog() const {
        if(buildFeature::config::isDbg())
            log();
    }

    const callstack& me::getStack() const {
        return _stack;
    }

    void me::logStack() const {
        _stack.dump();
        _logNativeStack();
    }

    void me::_logNativeStack() const {
        auto native = platformAPI::callstack();
        if(native.size() <= 0) return;

        logger& log = logger::get();
        using platformAPI::foreColor;
        log.logFormatBypass("\t%s----------------------------------%s\n", foreColor(BROWN).c_str(), foreColor(LIGHTGRAY).c_str());
        for(const std::string& trace : native) {
            log.logFormatBypass("\tat %s%s%s\n", foreColor(BLUE).c_str(), trace.c_str(), foreColor(LIGHTGRAY).c_str());
        }
    }

    void me::dump() const {
        log();
        logStack();
    }

    std::string me::_format(const std::string& fmt, va_list args) {
        nchar buf[MAX_BUF] = {0, };
        vsnprintf(buf, MAX_BUF, fmt.c_str(), args);

        return buf;
    }

    dummyErr::dummyErr(): super(logLv::ERR, 0) {}

    void dummyErr::log() const {}

}
