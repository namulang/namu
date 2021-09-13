#include "cppPackLoading.hpp"

namespace wrd {

    WRD_DEF_ME(cppPackLoading)

    static constexpr const wchar* ENTRYPOINT_NAME = "wrd_bridge_cpp_entrypoint";
    static srcs dummySrcs;

    tpair<origins&, srcs&> me::make() {
        super::make();

        tpair<origins&, srcs&> ret(_getOrigins(), dummySrcs);
        for(const std::string& path : _getPaths()) {
            // With the current implementation, it is not yet possible to create an srcs
            // object for a C++ class.
            // ret.r variables won't be assigned to new data till this procedure has done.
            if(!_loadLibs()) {
                _getOrigins().rel();
                return WRD_E("couldn't load c++ library at %s", path.c_str()), ret;
            }
        }

        return ret;
    }

    wbool me::_loadLibs() {
        libHandle newHandle = nullptr;
        for(const std::string& path : _getPaths()) {
            newHandle = dlopen(path.c_str(), RTLD_LAZY);
            if(!newHandle) {
                WRD_E("couldn't open %s pack: %s", path.c_str(), dlerror());
                goto FINALIZE;
            }

            entrypointFunc ep = (entrypointFunc) dlsym(newHandle, ENTRYPOINT_NAME);
            if(!ep) {
                WRD_E("couldn't locate entrypoint of %s pack: %s", path.c_str(), dlerror());
                goto FINALIZE;
            }

            ep(&_getOrigins());
            if(getOrigins().len() <= 0) {
                WRD_W("pack returns no origin object.");
                goto FINALIZE;
            }

            _handles.push_back(newHandle); // don't close yet.
            WRD_I("pack[%s] loads origins from %s", getName().c_str(), path.c_str());
        }

        WRD_I("pack[%s] origins loaded.", getName().c_str());
        return true;

FINALIZE:
        if(newHandle)
            dlclose(newHandle);
        me::rel();
        return false;
    }
}
