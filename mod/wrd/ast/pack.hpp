#pragma once

#include "manifest.hpp"
#include "../loader/pack/packLoading.hpp"
#include "../loader/pack/packMakable.hpp"
#include "../loader/errReport.hpp"
#include "scope.hpp"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;
    typedef tnmap<std::string, node, immutableTactic> scope;
    typedef tnchain<std::string, node, scope> scopes;
    class _wout pack : public obj, public packMakable {
        WRD(CLASS(pack, obj))

    public:
        enum state {
            RELEASED = 0,
            PARSED = 1,
            VERIFIED,
            LINKED,
        };

    public:
        pack(const manifest& manifest, const packLoadings& loadingsInHeap);
        ~pack() override;

    public:
        using super::subs;
        nbicontainer& subs() override;

        manifest& getManifest();
        const manifest& getManifest() const;
        state getState() const;
        wbool isValid() const;

        /// this report will be used while interpret pack source code.
        /// @remark when 'subs()' func of the pack has been called, it interprets src codes
        ///         if it's first time. during parsing and verification, this report will
        ///         collects warning & errors.
        ///         this func usually will be called by verifier when it detects the access
        ///         to a pack.
        ///         please refer 'verifier' class if you want to know further.
        void setReport(errReport& rpt);

        using super::run;
        // running of a pack is prohibited.
        str run(const ucontainable& args) override;
        wbool canRun(const ucontainable& args) const override;
        const pack& getOrigin() const override;

        void rel() override;
        void addDependent(pack& dependent);
        const tnarr<pack>& getDependents() const;
        void setValid(wbool valid);

    private:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override;
        wbool verify(errReport& rpt, pack& pak) override;
        wbool link();
        wbool invalidate();
        void _rel();

    private:
        tstr<scopes> _subs;
        packLoadings _loadings;
        manifest _manifest;
        state _state;
        wbool _isValid;
        srcs _srcs;
        tnarr<pack> _dependents;
        tstr<errReport> _rpt;
    };

    typedef tnmap<std::string, pack> packs;
    typedef tnchain<std::string, pack> packChain;
    typedef tnbicontainer<std::string, pack> packContainer;

#include "../common/MSVCHack.hpp"
}
