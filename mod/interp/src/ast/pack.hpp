#pragma once

#include "obj.hpp"
#include "manifest.hpp"
#include "../loader/packLoading.hpp"
#include "../loader/packMakable.hpp"

typedef wrd::tnarr<wrd::obj> origins;

namespace wrd {

    class pack : public node, public packMakable {
        WRD(CLASS(pack, node))

    public:
        pack(const manifest& manifest, const packLoadings& loadingsInHeap)
            : super(), _loadings(loadingsInHeap), _manifest(manifest), _isVerified(false) {}

        using super::subs;
        ncontainer& subs() override {
            return _origins;
        }

        manifest& getManifest() { return _manifest; }
        const manifest& getManifest() const { return _manifest; }

        origins& make() override {
            for(packLoading* load : _loadings)
                _origins.add(load->make());
            return _origins;
        }
        wbool verify(const packChain& mergedPacks) override {
            for(packLoading* load : _loadings)
                if(!load->verify(mergedPacks))
                    return false;

            return true;
        }
        wbool link(const packChain& mergedPacks) override {
            for(packLoading* load : _loadings)
                if(!load->link(mergedPacks))
                    return false;
            return true;
        }

        str run(const ncontainer& args) override { return str(); }
        wbool canRun(const wtypes& types) const override { return false; }

        wbool isValid() const override {
            if(!_manifest.isValid()) return false;

            return super::isValid();
        }

        const std::string& getName() const override {
            return _manifest.name;
        }

        void rel() override {
            super::rel();

            _origins.rel();
            _isVerified = false;
            for(packLoading* e : _loadings) {
                e->rel();
                delete e;
            }
            _loadings.clear();
        }

    private:
        packLoadings _loadings;
        manifest _manifest;
        wbool _isVerified;
        origins _origins;
    };

    typedef tnarr<pack> packs;
    typedef tnchain<pack> packChain;
}
