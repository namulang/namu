#pragma once

#include "obj.hpp"
#include "manifest.hpp"

namespace wrd {

    class pack : public node {
        WRD_CLASS(pack, node)

    public:
        pack(const std::string& filePath): super(), _subs(new narr()) {
            _manifest.filePath = filePath;
            _loadManifest(_manifest);
        }
        pack(const me& rhs) { _assign(rhs); }

        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

        using super::subs;
        ncontainer& subs() override {
            if(_subs) return super::subs();

            _subs = _loadOrigins(getName());
            return *_subs;
        }

        manifest& getManifest() { return _manifest; }
        const manifest& getManifest() const { return _manifest; }
        str run(const ncontainer& args) override { return str(); }
        wbool canRun(const wtypes& types) const override { return false; }

    private:
        tstr<nchain> _loadOrigins(const std::string& path) {
            // TODO: we know which entrypoints was belonged to this pack file.
            //  -> standby originExtractor matched to those entrypoints
            //  -> extraction all origins
            //  -> stack up this 'ret' value.
            tstr<nchain> ret;
            return ret;
        }
        void _loadManifest(manifest& man) const {
            // TODO: open pack zip file -> extract manifest.swrd file -> interpret it & load values
        }

        me& _assign(const me& rhs) {
            _manifest = rhs._manifest;
            _filePath = rhs._filePath;
            return *this;
        }

    private:
        manifest _manifest;
        std::string _filePath;
        tstr<narr> _subs;
    };
}
