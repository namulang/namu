#pragma once

#include "../../../ast/node.hpp"
#include "tnucontainer.hpp"
#include "../tarrayable.hpp"

namespace namu {

    class _nout nseq : public tnucontainer<nint>, public tarrayable<nint> {
        NAMU(CLASS(nseq, tnucontainer<nint>))
        friend class seq;

    public:
#include "../iter/nseqIteration.hpp"

    public:
        nseq(nint start, nint end);
        nseq(nint start, nint end, nint step);

    public:
        using tarrayable<nint>::operator[];
        virtual nint& operator[](nidx n) override;

    public:
        nint getStart() const;
        nint getEnd() const;
        nint getStep() const;

        ncnt len() const override;

        void rel() override;

        nint& get(nidx n) override;

        nbool has(nidx n) const override;

    protected:
        iteration* _onMakeIteration(ncnt step) const override;

    private:
        // these method has been prohibited.
        using super::add;
        using tarrayable<nint>::add;
        nbool add(const iter& at, const nint& new1) override;
        void add(const iter& at, const iter& from, const iter& to) override;
        nbool add(nidx n, const nint& new1) override;
        using super::set;
        using tarrayable<nint>::set;
        nbool set(const iter& at, const nint& new1) override;
        nbool set(nidx n, const nint& new1) override;
        using super::del;
        using tarrayable<nint>::del;
        nbool del(const iter& it) override;
        nbool del(const iter& from, const iter& end) override;
        nbool del(nidx n) override;

        void _updateStep();

    private:
        nint _start;
        nint _end;
        nint _step;
    };
}
