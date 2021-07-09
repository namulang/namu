#pragma once

#include "obj.hpp"
#include "manifest.hpp"

namespace wrd {

    class pack : public node {
        WRD_INTERFACE(pack, node)

    public:
        pack(const manifest& manifest): super(), _manifest(manifest) {}
        pack(const me& rhs) { _assign(rhs); }

        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            super::operator=(rhs);

            return _assign(rhs);
        }

        using super::subs;
        ncontainer& subs() override {
            if (!_subs)
                _subs = _loadOrigins(_manifest.points[0].paths);
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

        const std::string& getName() const override {
            return _manifest.name;
        }

        void rel() override {
            if(_subs)
                _subs->rel();

            super::rel();
        }

    protected:
        virtual tstr<narr> _loadOrigins(const std::vector<std::string>& filePaths) = 0;

    private:
        me& _assign(const me& rhs) {
            _manifest = rhs._manifest;
            _filePath = rhs._filePath;
            _subs = rhs._subs;

            return *this;
        }

    private:
        manifest _manifest;
        std::string _filePath;
        tstr<narr> _subs;
    };
}
