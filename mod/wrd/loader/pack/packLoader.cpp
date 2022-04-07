#include "packLoader.hpp"
#include "../../frame/thread.hpp"
#include "../errReport.hpp"

namespace wrd {

    WRD_DEF_ME(packLoader)

    me::packLoader(): _basePacks(nullptr), _report(dummyErrReport::singletone) {}

    tstr<packs> me::load() {
        // TODO: returns result when it's fail
        packs* ret = new packs();

        _makePacks(*ret);
        return tstr<packs>(*ret);
    }

    manifest me::_interpManifest(const std::string& dir, const std::string& manPath) const {
        // TODO: open pack zip file -> extract manifest.swrd file -> interpret it & load values
        tstr<sobj> loaded = sinterpreter().interpFile(manPath);
        if(!loaded)
            return WRD_E("error to load %s: interpretion err", manPath.c_str()), manifest();

        std::string name = loaded->sub("name").asStr();
        std::string ver = loaded->sub("ver").asStr();
        std::string author = loaded->sub("author").asStr();

        entrypoints points;
        sobj& entrypoints = loaded->sub("entrypoints");
        for(auto& pair: entrypoints) {
            const std::string& path = dir + DELIMITER + pair.second->sub("path").asStr();
            if(nul(path))
                return WRD_E("error to load %s: no entrypoint path", manPath.c_str()), manifest();

            // TODO: path should be multiple
            points.push_back(entrypoint {pair.first, {path}});
        }

        // post: all data interpreted. merge to manifest.
        return manifest {name, manPath, author, ver, points};
    }

    const packLoadings& me::_getLoadings() const {
        static packLoadings* inner = nullptr;
        if(!inner) {
            inner = new packLoadings();
            for(const type* sub : ttype<packLoading>::get().getLeafs()) {
                packLoading* new1 = sub->makeAs<packLoading>();
                if(nul(new1)) {
                    WRD_E("fail to make packMaking named to %s", sub->getName().c_str());
                    continue;
                }

                inner->push_back(new1);
            }
        }

        return *inner;
    }

}
