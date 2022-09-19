#pragma once

#include "err.hpp"
#include "../type/ntype.hpp"
#include "../common.hpp"

namespace namu {

    class _nout errReport : public instance {
        NAMU(CLASS(errReport, instance))

    public:
        const err& operator[](nidx n) const;
        operator nbool() const;

    public:
        nbool hasErr() const;
        nbool hasWarn() const;
        nbool has(err::type type) const;

        const err& get(nidx n) const;

        ncnt len() const;

        virtual const err& add(const err* new1);

        std::vector<tstr<err>>::const_iterator begin() const;
        std::vector<tstr<err>>::const_iterator end() const;

        void log() const;

        void rel();

    private:
        std::vector<tstr<err>> _errs;
    };

    class _nout dummyErrReport : public errReport {
        NAMU(CLASS(dummyErrReport, errReport))

    public:
        const err& add(const err* new1) override;

        static me singletone;
    };
}
