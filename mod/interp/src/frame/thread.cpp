#include "thread.hpp"
#include "../loader/packLoader.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packLoader& me::getPackLoader() {
        static packLoader* inner = nullptr;

        if(!inner) {
            inner = new packLoader({"pack/"});

            WRD_I("initiates loading system packs.");
            inner->load();
            WRD_I("%d system packs has been loaded.", inner->subs().len());

#ifdef WRD_IS_DBG
            WRD_I("next following is list for them.");
            for(const node& pak : inner->subs()) {
                const pack& cast = pak.cast<pack>();
                if(nul(cast)) {
                    WRD_E("cast isn't type of pack&");
                    continue;
                }

                WRD_DI(" - %s v%s", cast.getName().c_str(), cast.getManifest().version.c_str());
            }
#endif
        }

        return *inner;
    }
}
