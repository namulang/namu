#pragma once

#include "errCode.hpp"
#include "../ast/point.hpp"
#include "../common/namuMetaExtension.hpp"
#include "../type/ntype.hpp"
#include <unordered_map>

namespace namu {

    typedef std::unordered_map<nidx, std::string> msgMap;

    struct _nout err : public instance {
        NAMU(ME(err, instance),
            TYPE(ntype),
            INIT_META(me))

    public:
        enum type {
            ERR = 0,
            WARN,
            INFO,
        };

    public:
        err(err::type t, nint newCode, ...);
        err(err::type t, int newCode, va_list args);

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
        static constexpr nint BASE_TEST_CODE = 99999990; // not to be duplicated.

    private:
        std::string _format(const std::string& fmt, va_list args);
    };

    struct _nout dummyErr : public err {
        NAMU(ME(dummyErr, err),
            TYPE(ntype),
            INIT_META(me))

    public:
        dummyErr();

    public:
        void log() const override;
    };

    struct _nout srcErr : public err {
        NAMU(ME(srcErr, err),
            TYPE(ntype),
            INIT_META(me))

    public:
        template <typename... Args>
        srcErr(err::type t, const point& ps, int code, Args... args): super(t, code, args...), pos(ps) {}

    public:
        void log() const override;

    public:
        point pos;
    };
}
