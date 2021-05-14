#pragma once

#include "pack.hpp"

namespace wrd {

    class packLoader : public node {
        WRD_CLASS(packLoader, node)

    public:
        packLoader(): _subs(new nchain()) {}

        wbool canRun(const wtypes& types) const override {
            return false;
        }

        str run(const ncontainer& args) override {
            return str();
        }

        static const packLoader& get() {
            return _systemLoader;
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

    private:
        static packLoader _systemLoader;
        tstr<nchain> _subs;
    };
}
