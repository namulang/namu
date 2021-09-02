#pragma once

#include "../../../loader/opaquePackLoading.hpp"

namespace wrd {

    typedef void* libHandle;
    typedef std::vector<libHandle> libHandles;

    class cppPackLoading : public opaquePackLoading{
        WRD(CLASS(cppPackLoading, opaquePackLoading))
        typedef void (*entrypointFunc)(origins*);

    public:
        origins& make() override {
            origins& org = _getOrigins();
            for(const std::string& path : _getPaths()) {
                if(!_loadLibs(org)) {
                    org.rel();
                    return WRD_E("couldn't load c++ library at %s", path.c_str()), org;
                }
            }

            return org;
        }

        const std::string& getName() const override {
            static std::string inner = "cpp";
            return inner;
        }

        void rel() override {
            for(libHandle e : _handles)
                if(e)
                    dlclose(e);
            _handles.clear();

            super::rel();
        }

    private:
        wbool _loadLibs(origins& loadedClass);

    private:
        libHandles _handles;
    };
}
