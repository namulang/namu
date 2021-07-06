#pragma once

#include "packMaking.hpp"
#include "../ast/manifest.hpp"

namespace wrd {

    class packMaker {
        WRD_DECL_ME(packMaker)
        WRD_INIT_META(me)

    public:
        pack* makeWith(const manifest& mani) {
            const std::string& lang = mani.points[0].lang;
            const packMaking& making = _getMaking(lang);
            if(nul(making))
                return WRD_E("language '%s' not supported.", lang.c_str()), nullptr;

            return making.makeWith(mani);
        }

    private:
        const packMaking& _getMaking(const std::string& name) const {
            for(const packMaking* e : _getMakings()) {
                if(e->getName() == name) return *e;
            }

            WRD_W("can't find exact packMaking like %s", name.c_str());
            return nulOf<packMaking>();
        }

        static const packMakings& _getMakings();
    };
}
