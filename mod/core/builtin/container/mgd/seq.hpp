#pragma once

#include "../../../ast.hpp"
#include "../native/nseq.hpp"
#include "../../../bridge/cpp/tcppBridge.hpp"

namespace namu {

    // another f**king annoying MSVC Hack:
    //  to avoid C2901 error, I need to declare sort of dllexport(import) things at here.
    //  spended plenty of hours again to find out the reason. thank you so much.
    typedef class _nout tcppBridge<nseq> __seqSuperClass;

    class _nout seq : public __seqSuperClass, public tucontainable<nint>, tarrayable<nint> {
        NAMU(CLASS(seq, __seqSuperClass), VISIT())
        typedef typename tucontainable<nint>::iter iter;
        typedef typename tucontainable<nint>::iteration iteration;

    public:
        seq(nint start, nint end);
        seq(nint start, nint end, nint step);

    public:
        using tarrayable<nint>::operator[];
        nint& operator[](nidx n) override { return get()[n]; }

    public:
        const node& getElemType() const {
            static nInt inner;
            return inner;
        }

        using super::subs;
        nbicontainer& subs() override;

        ncnt len() const override { return get().len(); }

        nbool has(nidx n) const override { return get().has(n); }

        //  get:
        using tarrayable<nint>::get;
        using super::get;
        nint& get(nidx n) override { return get().get(n); }

        //  etc:
        void rel() override { return get().rel(); }

    protected:
        iteration* _onMakeIteration(ncnt step) const override;

    private:
        // these method has been prohibited.
        //  set:
        using tucontainable<nint>::set;
        using tarrayable<nint>::set;
        nbool set(const iter& at, const nint& new1) override { return false; }
        nbool set(nidx n, const nint& new1) override { return false; }
        //  add:
        using tucontainable<nint>::add;
        using tarrayable<nint>::add;
        nbool add(const iter& at, const nint& new1) override { return false; }
        nbool add(nidx n, const nint& new1) override { return false; }
        void add(const iter& here, const iter& from, const iter& to) override {}
        //  del:
        using tucontainable<nint>::del;
        nbool del(nidx n) override { return false; }
        nbool del(const iter& it) override { return false; }
        nbool del(const iter& from, const iter& to) override { return false; }
    };
}
