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
        nseq(nint start, nint end): _start(start), _end(end) { _updateStep(); }
        nseq(nint start, nint end, nint step): _start(start), _end(end), _step(step) {}

    public:
        using tarrayable<nint>::operator[];
        virtual nint& operator[](nidx n) override {
            return get(n);
        }

    public:
        nint getStart() const { return _start; }
        nint getEnd() const { return _end; }
        nint getStep() const { return _step; }

        ncnt len() const override;

        void rel() override {}

        using tarrayable<nint>::get;
        nint& get(nidx n) override;

        nbool has(nidx n) const override;

    protected:
        iteration* _onMakeIteration(ncnt step) const override;

    private:
        // these method has been prohibited.
        using super::getAll;
        using super::add;
        using tarrayable<nint>::add;
        nbool add(const iter& at, const nint& new1) override { return false; }
        void add(const iter& at, const iter& from, const iter& to) override {}
        nbool add(nidx n, const nint& new1) override { return false; }
        using super::set;
        using tarrayable<nint>::set;
        nbool set(const iter& at, const nint& new1) override { return false; }
        nbool set(nidx n, const nint& new1) override { return false; }
        using super::del;
        using tarrayable<nint>::del;
        nbool del(const iter& it) override { return false; }
        nbool del(const iter& from, const iter& end) override { return false; }
        nbool del(nidx n) override { return false; }

        void _updateStep() {
            _step = _end >= _start ? 1 : -1;
        }

    private:
        nint _start;
        nint _end;
        nint _step;
    };
}
