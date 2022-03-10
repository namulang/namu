#pragma once

#include "obj.hpp"
#include "manifest.hpp"
#include "../loader/pack/packLoading.hpp"
#include "../loader/pack/packMakable.hpp"
#include "../loader/errReport.hpp"

namespace wrd {

    class func;
    typedef tnarr<func> funcs;

    class pack : public obj, public packMakable {
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
        ncontainer& subs() override {
            ncontainer& subs = super::subs();
            if(_state == RELEASED) {
                WRD_I("%s pack is about to interpret lazy.", getName().c_str());
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
        str run(const containable& args) override { return str(); }

        wbool canRun(const containable& args) const override { return false; }

        const std::string& getName() const override {
            return _manifest.name;
        }

        wbool setName(const std::string& new1) override {
            _manifest.name = new1;
            return true;
        }

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
        tstr<srcs> parse(errReport& rpt, containable& tray) override {
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
            for(auto e = _dependents.begin<pack>(); e ; ++e)
                e->invalidate();
            return true;
        }

        void _rel();

    private:
        narr _subs;
        packLoadings _loadings;
        manifest _manifest;
        state _state;
        wbool _isValid;
        srcs _srcs;
        tnarr<pack> _dependents;
        tstr<errReport> _rpt;
    };

    typedef tnarr<pack> packs;
    typedef tnchain<pack> packChain;
}
