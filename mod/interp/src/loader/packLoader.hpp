#pragma once

#include "../ast/pack.hpp"

namespace wrd {

    class packLoader : public node {
        WRD_CLASS(packLoader, node)

    public:
        packLoader(std::initializer_list<const wchar*> paths)
            : _subs(new nchain()) {
            _init(paths);
        }

        wbool canRun(const wtypes& types) const override {
            return false;
        }

        str run(const ncontainer& args) override {
            return str();
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

    private:
        void _init(std::initializer_list<const wchar*> paths);

    private:
        tstr<nchain> _subs;
    };
}
