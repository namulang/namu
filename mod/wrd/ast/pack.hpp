#pragma once

#include "obj.hpp"
#include "manifest.hpp"
#include "../loader/pack/packLoading.hpp"
#include "../loader/pack/packMakable.hpp"
#include "../loader/errReport.hpp"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

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
        nbicontainer& subs() override {
            nbicontainer& subs = *_subs;
            if(_state == RELEASED) {
                WRD_I("%s pack is about to interpret lazy.", _manifest.name.c_str());
                // TODO: check _rpt error count increased or not.
                //       if increased, then parse() function has been failed.
                parse(*_rpt, subs); // recursive call wasn't allowed.
                verify(*_rpt, *this);
                link();
            }

            return subs;
        }

        manifest& getManifest() { return _manifest; }
        const manifest& getManifest() const { return _manifest; }
        state getState() const { return _state; }
        wbool isValid() const { return _isValid; }
        /// this report will be used while interpret pack source code.
        /// @remark when 'subs()' func of the pack has been called, it interprets src codes
        ///         if it's first time. during parsing and verification, this report will
        ///         collects warning & errors.
        ///         this func usually will be called by verifier when it detects the access
        ///         to a pack.
        ///         please refer 'verifier' class if you want to know further.
        void setReport(errReport& rpt) {
            _rpt.bind(rpt);
        }

        using super::run;
        // running of a pack is prohibited.
        str run(const ucontainable& args) override { return str(); }

        wbool canRun(const ucontainable& args) const override { return false; }

        const pack& getOrigin() const override {
            return *this;
        }

        funcs& getCtors() override;

        void rel() override {
            super::rel();
            _rel();
        }

        void addDependent(pack& dependent) {
            _dependents.add(dependent);
        }

        const tnarr<pack>& getDependents() const {
            return _dependents;
        }

        void setValid(wbool valid) {
            _isValid = valid;
        }

    private:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override {
            // You shouldn't release instances which _subs is holding:
            //  there is a scenario which _subs containing parsed instance when
            //  this function called.
            //  Only you can do here is adding new parsed instances into _subs.
            for(packLoading* load : _loadings) {
                auto res = load->parse(rpt, tray);
                _srcs.add(*res);
            }
            _state = PARSED;
            return tstr<srcs>(_srcs);
        }

        wbool verify(errReport& rpt, pack& pak) override {
            for(packLoading* load : _loadings)
                load->verify(rpt, pak);

            _state = VERIFIED;
            return true;
        }

        wbool link() {
            _state = LINKED;
            return !isValid() ? invalidate() : true;
        }

        wbool invalidate() {
            setValid(false);
            if(_state != LINKED) return false;

            // propagate result only if it's not valid.
            for(auto& e : _dependents)
                if(e.isSub<pack>())
                    e.cast<pack>().invalidate();
            return true;
        }

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
}
