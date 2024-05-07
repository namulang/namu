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

    me::err(logLv::level t, nint newCode): super(), fType(t), code((errCode) newCode), _stack(_extractStack()) {}

    me::err(logLv::level t, nint newCode, va_list args): super(), fType(t), code((errCode) newCode) {
        msg = _format(getErrMsg(code), args);
        _stack.setStack(_extractStack());
    }

    me::err(logLv::level t, const point& ps, nint newCode, va_list args)
        : super(), fType(t), code((errCode) newCode), pos(ps) {
        msg = _format(getErrMsg(code), args);
        _stack.setStack(_extractStack());
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
                std::cerr << foreColor(LIGHTRED);
                if(pos.isOrigin())
                    log.logFormatBypass("err%d(%s)", code, getErrName(code).c_str());
                else
                    log.logFormatBypass("err%d(%s) %d:%d", code, getErrName(code).c_str(), pos.row, pos.col);
                std::cerr << foreColor(LIGHTGRAY);
                log.logFormatBypass(": %s\n", msg.c_str());
                break;

            case logLv::WARN:
                std::cerr << foreColor(YELLOW);
                if(pos.isOrigin())
                    log.logFormatBypass("warn%d(%s)", code, getErrName(code).c_str());
                else
                    log.logFormatBypass("warn%d(%s) %d:%d", code, getErrName(code).c_str(), pos.row, pos.col);
                std::cerr << foreColor(LIGHTGRAY);
                log.logFormatBypass(": %s\n", msg.c_str());
                break;

            case logLv::INFO:
                std::cerr << foreColor(BLUE);
                if(pos.isOrigin())
                    log.logFormatBypass("info%d(%s)", code, getErrName(code).c_str());
                else
                    log.logFormatBypass("info%d(%s) %d:%d", code, getErrName(code).c_str(), pos.row, pos.col);
                std::cerr << foreColor(LIGHTGRAY);
                log.logFormatBypass(": %s\n", msg.c_str());
                break;
        }
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

    const scopes& me::_extractStack() const {
        const frame& fr = thread::get().getNowFrame();
        if(nul(fr)) return nulOf<scopes>();

        return fr.subs().cast<scopes>();
    }


    dummyErr::dummyErr(): super(logLv::ERR, 0) {}

    void dummyErr::log() const {}

}
