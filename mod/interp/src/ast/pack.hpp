#pragma once

#include "obj.hpp"

namespace wrd {

    class pack : public node {
        WRD_CLASS(pack, node)

        struct manifest {
            std::string name;
            std::string packPath; // it's a logical identifier. not a physical path of the actual file.
            /*
             * version, author, github url, backward compat., dependencies...
             */
        };

    public:
        pack(const std::string& filePath): super(), _filePath(filePath), _subs(new narr()) {}
        pack(const me& rhs) {
            _assign(rhs);
        }

        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

        ~pack() {
            if(_manifest)
                delete _manifest;
        }

        using super::subs;
        ncontainer& subs() override {
            if(_subs) return super::subs();

            _subs = _onLoadOrigins(getName());
            return *_subs;
        }

        manifest& getManifest() {
            if(!_manifest) _manifest = _onLoadManifest(getName());
            return *_manifest;
        }

        const manifest& getManifest() const WRD_UNCONST_FUNC(getManifest())

        str run(const ncontainer& args) override {
            return str();
        }

        wbool canRun(const wtypes& types) const override {
            return false;
        }

    private:
        tstr<nchain> _onLoadOrigins(const std::string& path) {
            // TODO: we know which entrypoints was belonged to this pack file.
            //  -> standby originExtractor matched to those entrypoints
            //  -> extraction all origins
            //  -> stack up this 'ret' value.
            tstr<nchain> ret;
            return ret;
        }
        manifest* _onLoadManifest(const std::string& path) const {
            // TODO: open pack zip file -> extract manifest.swrd file -> interpret it & load values
            manifest* ret = new manifest();
            return ret;
        }

        me& _assign(const me& rhs) {
            if (_manifest)
                delete _manifest;

            _manifest = new manifest(*rhs._manifest);
            _filePath = rhs._filePath;
            return *this;
        }

    private:
        manifest* _manifest;
        std::string _filePath;
        tstr<narr> _subs;
    };
}
