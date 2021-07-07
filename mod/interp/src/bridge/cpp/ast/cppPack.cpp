#include "cppPack.hpp"
#include "../../../builtin/container/native/tnarr.inl"

namespace wrd {

    WRD_DEF_ME(cppPack)

    static constexpr const wchar* ENTRYPOINT_NAME = "";

    tstr<nchain> me::_loadOrigins(const std::vector<std::string>& filePaths) {
        if(filePaths.size() <= 0)
            return WRD_E("no entrypoints provided."), tstr<nchain>();

        narr orgs;
        for(const std::string& path : filePaths) {
            libHandle newHandle = dlopen(path.c_str(), RTLD_LAZY);
            if(!newHandle) {
                WRD_E("couldn't open %s pack: %s", path.c_str(), dlerror());
                continue;
            }

            entrypointFunc func = (entrypointFunc) dlsym(newHandle, ENTRYPOINT_NAME);
            if(!func) {
                WRD_E("couldn't locate entrypoint of %s pack: %s", path.c_str(), dlerror());
                dlclose(newHandle);
                continue;
            }

            wrd_bridge_cpp_origins tray;
            func(&tray);
            if(tray.len() <= 0) {
                WRD_W("pack returns no origin object.");
                dlclose(newHandle);
                continue;
            }

            orgs.add(tray);
            _handles.push_back(newHandle); // don't close yet.
            WRD_I("pack[%s] loads origins from %s", getName().c_str(), path.c_str());
        }

        WRD_I("pack[%s] origins loaded.", getName().c_str());
        return tstr<nchain>(new nchain(orgs));
    }

    void me::_rel() {
        for(libHandle h : _handles)
            dlclose(h);
    }
}
