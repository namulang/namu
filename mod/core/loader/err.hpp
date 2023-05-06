#pragma once

#include "errCode.hpp"
#include "../ast/point.hpp"
#include "../common/namuMetaExtension.hpp"
#include "../type/ntype.hpp"
#include <unordered_map>

namespace namu {

    typedef std::unordered_map<nidx, std::string> msgMap;

    class pos;
    struct _nout err : public instance {
        NAMU(CLASS(err, instance))

    public:
        enum type {
            ERR = 0,
            WARN,
            INFO,
        };

    public:
        err(err::type t, nint newCode);
        err(err::type t, nint newCode, va_list args);
        err(err::type t, const point& ps, nint newCode, va_list args): super(), fType(t), code((errCode) newCode), pos(ps) {
            msg = _format(getErrMsg(code), args);
        }

    public:
        virtual void log() const;
        void dbgLog() const;

        static const std::string& getErrMsg(errCode code);
        static const std::string& getErrName(errCode code);
        static err* newErr(int code, ...);
        static err* newErr(const point& src, int code, ...);
        static err* newWarn(int code, ...);
        static err* newWarn(const point& src, int code, ...);
        static err* newInfo(int code, ...);
        static err* newInfo(const point& src, int code, ...);

    public:
        err::type fType;
        errCode code;
        std::string msg;
        point pos;
        static constexpr nint BASE_TEST_CODE = 99999990; // not to be duplicated.

    private:
        std::string _format(const std::string& fmt, va_list args);
    };

    struct _nout dummyErr : public err {
        NAMU(CLASS(dummyErr, err))

    public:
        dummyErr();

    public:
        void log() const override;
    };
}
