#pragma once

#include "manifest.hpp"
#include "../loader/errReport.hpp"

namespace wrd {

    class _wout slot : public instance {
        WRD(CLASS(slot, instance))

    public:
        slot(const manifest& manifest);
        slot(const manifest& manifest, const obj& pack);
        ~slot() override;

    public:
        manifest& getManifest();
        const manifest& getManifest() const;
        wbool isValid() const;
        virtual obj& getPack();
        const obj& getPack() const WRD_UNCONST_FUNC(getPack())
        wbool setPack(const obj& newPack);

        void rel() override;
        void addDependent(me& dependent);
        const tnarr<me>& getDependents() const;

    protected:
        wbool _invalidate();
        void _setValid(wbool valid);

    private:
        void _rel();

    private:
        tstr<obj> _pak;
        manifest _manifest;
        wbool _isValid;
        srcs _srcs;
        tnarr<me> _dependents;
    };

    typedef tnmap<std::string, slot> slots;
    typedef tnchain<std::string, slot> slotChain;
    typedef tnbicontainer<std::string, slot> slotContainer;

#include "../common/MSVCHack.hpp"
}
