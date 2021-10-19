#include "thread.hpp"
#include "../loader/pack/packLoader.hpp"
#include "../loader/errReport.hpp"
#include "../ast/node.inl"
#include "../ast/func.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packs& me::getSystemPacks() {
        static tstr<packs> inner;

        if(!inner) {
            packLoader loader;

            WRD_I("initiates loading system packs.");
            errReport report;
            inner = loader.setReport(report).addPath("pack/").load();
            WRD_I("%d system packs has been loaded.", inner->len());

#ifdef WRD_IS_DBG
            WRD_I("next following is list for them.");
            for(const node& pak : *inner) {
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

    str me::run(const containable& args) {
        // TODO: args validness check.

        // find 'main' func:
        func& fun = _root->sub<func>("main"); // TODO: support generic type of str[]
        if(nul(fun))
            return WRD_E("there is no 'main' func."), str();

        thread* prev = *_get();
        *_get() = this;
        str res = fun.run(args);
        *_get() = prev;

        return res;
    }
}
