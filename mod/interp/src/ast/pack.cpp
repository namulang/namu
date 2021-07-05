#include "pack.hpp"
#include "../loader/orgExtractor.hpp"

namespace wrd {

    WRD_DEF_ME(pack)

    manifest me::_interpManifest(const std::string& manPath) const {
        // TODO: open pack zip file -> extract manifest.swrd file -> interpret it & load values
        tstr<sobj> loaded = sinterpreter().interpFile(manPath);
        if(!loaded)
            return WRD_E("error to load %s: interpretion err", manPath.c_str()), manifest();

        std::string name = loaded->sub("name").asStr();
        std::string ver = loaded->sub("ver").asStr();
        std::string author = loaded->sub("author").asStr();

        entrypoints points;
        sobj& entrypoints = loaded->sub("entrypoints");
        orgExtractor extractor;
        for(auto& pair: entrypoints) {
            const std::string& lang = pair.first;
            if(nul(extractor.getExtraction(lang)))
                return WRD_E("error to load %s: lang '%s' unsupported.", manPath.c_str(), lang.c_str()), manifest();

            const std::string& path = pair.second->sub("path").asStr();
            if(nul(path))
                return WRD_E("error to load %s: no entrypoint path", manPath.c_str()), manifest();

            // TODO: path should be multiple
            entrypoint newPoint = {lang, {path}};
            points.push_back(newPoint);
        }

        // post: all data interpreted. merge to manifest.
        return manifest {name, manPath, author, ver, points};
    }
}
