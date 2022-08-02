#pragma once

#include "slot.hpp"
#include "../loader/pack/packLoading.hpp"
#include "../loader/pack/packMakable.hpp"
#include "scope.hpp"

namespace namu {

    class _wout autoslot : public slot, public packMakable {
        WRD(CLASS(autoslot, slot))

    public:
        enum state {
            RELEASED = 0,
            PARSED = 1,
            VERIFIED,
            LINKED,
        };

    public:
        autoslot(const manifest& manifest, const packLoadings& loadingsInHeap);
        ~autoslot() override;

    public:
        state getState() const;
        using super::getPack;
        obj& getPack() override;
        void rel() override;
        /// this report will be used while interpret pack source code.
        /// @remark when 'subs()' func of the pack has been called, it interprets src codes
        ///         if it's first time. during parsing and verification, this report will
        ///         collects warning & errors.
        ///         this func usually will be called by verifier when it detects the access
        ///         to a pack.
        ///         please refer 'verifier' class if you want to know further.
        void setReport(errReport& rpt);

    protected:
        wbool _invalidate() override;

    private:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override;
        wbool verify(errReport& rpt, obj& pak) override;
        wbool link();
        void _rel();

    private:
        packLoadings _loadings;
        state _state;
        srcs _srcs;
        tstr<errReport> _rpt;
    };
}
