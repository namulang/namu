#include "err.hpp"

namespace wrd {

    WRD_DEF_ME(err)

    namespace {
        constexpr wint MAX_BUF = 512;
    }

    const msgMap& err::getErrMsgs() {
        int id = 0;

#define _ON_MSG(TEXT) {id++, TEXT},

        static msgMap inner {
        WRD_EACH(_ON_MSG,
            "unknown", /* is 0 */
            "this expr doesn't have row info", // 1
            "this expr evaluated as nulled type",
            "%s tried to access '%s' but nothing exist",
            "obj can't be cast into node class",
            "obj can't execute with this argument types", // 5
            "this expr doesn't have col info",
            "syntax error %s expected, but %s found",
            "%s",
            "unexpected token '%s' found",
            "invalid indentation level found. expected %d columns but it was %d. I'm assuming you were trying to give %d columns", // 10
            "%s is null",
            "parsing has done. but something went wrong: %d",
            "%s pack hasn't been created before",
            "no pack has been specified",
            "\'%s\' object already exists at %s", // 15
            "\'%s\' isn't a expression",
            "wrong parameter syntax: %s",
            "parameter shouldn't have a value",
            "%s is not a expression declaring something",
            "a function should have a name", // 20
            "%s is not a valid return type",
            "return type is not specified",
            "function need to contain more than 1 statement inside",
            "function info doesn't exist",
            "%d return type isn't valid to %s return type of func", // 25
            "block statement failed to construct frame structure",

            /* to be continue... */

            "end of errors"
        )

#undef _ON_MSG

            // msg for TC:
            {BASE_TEST_CODE + 1, "val is 0"},
            {BASE_TEST_CODE + 2, "grade(%f) should be positive"},
        };

        return inner;
    }

    std::string me::_format(const std::string& fmt, va_list args) {
        wchar buf[MAX_BUF] = {0, };
        vsnprintf(buf, MAX_BUF, fmt.c_str(), args);

        return buf;
    }

#define _EXPAND_VA(EXPR) \
        va_list args; \
        va_start(args, errCode); \
        err* ret = EXPR; \
        va_end(args); \
        return ret

    err* me::newErr(wcnt errCode, ...) {
        _EXPAND_VA(new err(err::ERR, errCode, args));
    }
    err* me::newErr(const area& src, wcnt errCode, ...) {
        _EXPAND_VA(new srcErr(err::ERR, src, errCode, args));
    }
    err* me::newWarn(wcnt errCode, ...) {
        _EXPAND_VA(new err(err::WARN, errCode, args));
    }
    err* me::newWarn(const area& src, wcnt errCode, ...) {
        _EXPAND_VA(new srcErr(err::WARN, src, errCode, args));
    }
    err* me::newInfo(wcnt errCode, ...) {
        _EXPAND_VA(new err(err::INFO, errCode, args));
    }
    err* me::newInfo(const area& src, wcnt errCode, ...) {
        _EXPAND_VA(new srcErr(err::INFO, src, errCode, args));
    }

#undef _EXPAND_VA
}
