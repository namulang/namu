#include "thread.hpp"
#include "../loader/packLoader.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packChain& me::getPacks() {
        static packChain* inner = nullptr;
        if(!inner) {
            packs loadedPacks;
            inner = new packChain(loadedPacks);
            WRD_I("initiates loading system packs.");

            packLoader loader({"pack/"});
            WRD_I("%d system packs has been loaded.", loader.subs().len());

#ifdef WRD_IS_DBG
            WRD_I("next following is list for them.");
            for(const node& pak : loader.subs()) {
                const pack& cast = pak.cast<pack>();
                if(nul(cast)) {
                    WRD_E("cast isn't type of pack&");
                    continue;
                }

                WRD_DI(" - %s v%s", cast.getName().c_str(), cast.getManifest().version.c_str());
            }
#endif

            loadedPacks.add(loader.subs());
        }

        return *inner;
    }
}
