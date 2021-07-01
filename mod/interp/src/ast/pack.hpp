#pragma once

#include "obj.hpp"
#include "manifest.hpp"

namespace wrd {

    class pack : public node {
        WRD_CLASS(pack, node)

    public:
        pack(const std::string& filePath): super(), _subs(new narr()) {
            _manifest = _interpManifest(filePath);
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

            if (!_subs)
                _subs = _loadOrigins(getName());
            return *_subs;
        }

        manifest& getManifest() { return _manifest; }
        const manifest& getManifest() const { return _manifest; }
        str run(const ncontainer& args) override { return str(); }
        wbool canRun(const wtypes& types) const override { return false; }

        wbool isValid() const override {
            if(!_manifest.isValid()) return false;

            return super::isValid();
        }

    private:
        tstr<nchain> _loadOrigins(const std::string& path) {
            // TODO: we know which entrypoints was belonged to this pack file.
            //  -> standby originExtractor matched to those entrypoints
            //  -> extraction all origins
            //  -> stack up this 'ret' value.
            tstr<nchain> ret;
            return ret;
        }

        manifest _interpManifest(const std::string& manPath) const;

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
