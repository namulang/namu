#pragma once

#include "manifest.hpp"
#include "../loader/errReport.hpp"
#include "obj.hpp"

namespace namu {

    class visitor;

    class _nout slot : public node {
        NAMU(CLASS(slot, node), VISIT())

    public:
        slot(const manifest& manifest);
        slot(const manifest& manifest, const obj& pack);

    public:
        manifest& getManifest();
        const manifest& getManifest() const;
        nbool isValid() const;
        virtual obj& getPack();
        const obj& getPack() const NAMU_UNCONST_FUNC(getPack())
        void rel() override;
        void addDependent(me& dependent);
        const tnarr<me>& getDependents() const;

        using super::subs;
        nbicontainer& subs() override { return getPack().subs(); }

        nbool canRun(const args& a) const override { return getPack().canRun(a); }

        using super::run;
        str run(const args& a) override { return getPack().run(a); }

        const node& getEval() const override { return getPack().getEval(); }

    protected:
        virtual nbool _invalidate();
        void _setValid(nbool valid);
        virtual str _onRunSub(node& sub, const args& a) override {
            return getPack()._onRunSub(sub, a);
        }


    private:
        void _rel();

    protected:
        tstr<obj> _pak;

    private:
        manifest _manifest;
        nbool _isValid;
        tnarr<me> _dependents;
    };

    typedef tnmap<std::string, slot> slots;
    typedef tnchain<std::string, slot> slotChain;
    typedef tnbicontainer<std::string, slot> slotContainer;

#include "../common/MSVCHack.hpp"
}
