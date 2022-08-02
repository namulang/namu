#include "cppPackLoading.hpp"

namespace namu {

    WRD_DEF_ME(cppPackLoading)

    static constexpr const wchar* ENTRYPOINT_NAME = "namu_bridge_cpp_entrypoint";
    static srcs dummySrcs;

    tstr<srcs> me::parse(errReport& rpt, bicontainable& tray) {
        tstr<srcs> ret(dummySrcs);
        for(const std::string& path : _getPaths()) {
            // With the current implementation, it is not yet possible to create an srcs
            // object for a C++ class.
            // ret.r variables won't be assigned to new data till this procedure has done.
            if(!_loadLibs(rpt, tray)) {
                tray.rel();
                return WRD_E("couldn't load c++ library at %s", path.c_str()), ret;
            }
        }

        return ret;
    }

    wbool me::_loadLibs(errReport& rpt, bicontainable& tray) {
        // TODO: use 'rpt' variable.
        libHandle newHandle = nullptr;
        for(const std::string& path : _getPaths()) {
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            newHandle = LoadLibraryA(path.c_str());
#else
            newHandle = dlopen(path.c_str(), RTLD_LAZY);
#endif
            if(!newHandle) {
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
                WRD_E("couldn't open %s slot: %d", path.c_str(), GetLastError());
#else
                WRD_E("couldn't open %s slot: %s", path.c_str(), dlerror());
#endif
                goto FINALIZE;
            }

#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            entrypointFunc ep = (entrypointFunc) GetProcAddress(newHandle, ENTRYPOINT_NAME);
#else
            entrypointFunc ep = (entrypointFunc) dlsym(newHandle, ENTRYPOINT_NAME);
#endif
            if(!ep) {
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
                WRD_E("couldn't locate entrypoint of %s slot: %d", path.c_str(), GetLastError());
#else
                WRD_E("couldn't locate entrypoint of %s slot: %s", path.c_str(), dlerror());
#endif
                goto FINALIZE;
            }

            ep(&tray);
            if(tray.len() <= 0) {
                WRD_W("slot returns no origin object.");
                goto FINALIZE;
            }

            _handles.push_back(newHandle); // don't close yet.
            WRD_I("slot[%s] loads origins from %s", getName().c_str(), path.c_str());
        }

        WRD_I("slot[%s] origins loaded.", getName().c_str());
        return true;

FINALIZE:
        if(newHandle)
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            FreeLibrary(newHandle);
#else
            dlclose(newHandle);
#endif
        me::rel();
        return false;
    }

    void me::rel() {
        for (libHandle e : _handles)
            if (e)
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
                FreeLibrary(e);
#else
                dlclose(e);
#endif
        _handles.clear();

        super::rel();
    }

    const std::string& me::getName() const {
        static std::string inner = "cpp";
        return inner;
    }
}
