#pragma once

#include "err.hpp"
#include "../type/wtype.hpp"
#include "../ast/clonable.hpp"
#include "../common.hpp"

namespace namu {

    class _wout errReport : public instance, public clonable {
        WRD(CLASS(errReport, instance))

    public:
        const err& operator[](widx n) const;
        operator wbool() const;

    public:
        wbool hasErr() const;
        wbool hasWarn() const;
        wbool has(err::type type) const;

        const err& get(widx n) const;

        wcnt len() const;

        virtual const err& add(const err* new1);

        std::vector<tstr<err>>::const_iterator begin() const;
        std::vector<tstr<err>>::const_iterator end() const;

        void log() const;

        void rel();

    private:
        std::vector<tstr<err>> _errs;
    };

    class _wout dummyErrReport : public errReport {
        WRD(CLASS(dummyErrReport, errReport))

    public:
        const err& add(const err* new1) override;

        static me singletone;
    };
}
