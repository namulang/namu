#pragma once

#include "err.hpp"
#include "../type/ntype.hpp"
#include "../common.hpp"

namespace namu {

    class _nout errReport : public instance {
        NAMU(CLASS(errReport, instance))

    public:
        nbool operator==(const me& rhs) const {
            if(len() != rhs.len()) return false;

            for(nint n=0; n < len() ;n++)
                if(get(n) != rhs[n])
                    return false;
            return true;
        }
        nbool operator!=(const me& rhs) const {
            return !operator==(rhs);
        }

        const err& operator[](nidx n) const;
        operator nbool() const;

    public:
        nbool hasErr() const;
        nbool hasWarn() const;
        nbool has(err::type type) const;

        const err& get(nidx n) const;

        ncnt len() const;

        virtual const err& add(const err* new1);
        const err& add(const err& new1) { return add(&new1); }
        void add(const me& rhs);

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
