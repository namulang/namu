#pragma once

#include "manifest.hpp"
#include "../loader/errReport.hpp"
#include "obj.hpp"

namespace namu {

    class _wout slot : public node {
        WRD(CLASS(slot, node))

    public:
        slot(const manifest& manifest);
        slot(const manifest& manifest, const obj& pack);

    public:
        manifest& getManifest();
        const manifest& getManifest() const;
        wbool isValid() const;
        virtual obj& getPack();
        const obj& getPack() const WRD_UNCONST_FUNC(getPack())
        void rel() override;
        void addDependent(me& dependent);
        const tnarr<me>& getDependents() const;

        using super::subs;
        nbicontainer& subs() override { return getPack().subs(); }

        wbool canRun(const ucontainable& args) const override { return getPack().canRun(args); }

        using super::run;
        str run(const ucontainable& args) override { return getPack().run(args); }

        const node& getEval() const override { return getPack().getEval(); }

    protected:
        virtual wbool _invalidate();
        void _setValid(wbool valid);
        virtual str _onRunSub(node& sub, const ucontainable& args) override {
            return getPack()._onRunSub(sub, args);
        }


    private:
        void _rel();

    protected:
        tstr<obj> _pak;

    private:
        manifest _manifest;
        wbool _isValid;
        tnarr<me> _dependents;
    };

    typedef tnmap<std::string, slot> slots;
    typedef tnchain<std::string, slot> slotChain;
    typedef tnbicontainer<std::string, slot> slotContainer;

#include "../common/MSVCHack.hpp"
}
