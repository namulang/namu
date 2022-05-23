#include "../ast/node.hpp"
#include "err.hpp"

namespace wrd {

    WRD_DEF_ME(err)

    namespace {
        constexpr wint MAX_BUF = 512;
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

    std::string me::_format(const std::string& fmt, va_list args) {
        wchar buf[MAX_BUF] = {0, };
        vsnprintf(buf, MAX_BUF, fmt.c_str(), args);

        return buf;
    }

#define _EXPAND_VA(EXPR) \
        va_list args; \
        va_start(args, code); \
        err* ret = EXPR; \
        va_end(args); \
        return ret

    err* me::newErr(int code, ...) {
        _EXPAND_VA(new err(err::ERR, code, args));
    }
    err* me::newErr(const area& src, int code, ...) {
        _EXPAND_VA(new srcErr(err::ERR, src, code, args));
    }
    err* me::newWarn(int code, ...) {
        _EXPAND_VA(new err(err::WARN, code, args));
    }
    err* me::newWarn(const area& src, int code, ...) {
        _EXPAND_VA(new srcErr(err::WARN, src, code, args));
    }
    err* me::newInfo(int code, ...) {
        _EXPAND_VA(new err(err::INFO, code, args));
    }
    err* me::newInfo(const area& src, int code, ...) {
        _EXPAND_VA(new srcErr(err::INFO, src, code, args));
    }

#undef _EXPAND_VA
}
