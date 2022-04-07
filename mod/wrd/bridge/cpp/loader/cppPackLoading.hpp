#pragma once

#include "../../../loader/pack/opaquePackLoading.hpp"
#include "../../../ast/src.hpp"
#include "../../../ast/pack.hpp"

namespace wrd {

    typedef void* libHandle;
    typedef std::vector<libHandle> libHandles;

    class cppPackLoading : public opaquePackLoading{
        WRD(CLASS(cppPackLoading, opaquePackLoading))
        typedef void (*entrypointFunc)(bicontainable*);

    public:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override;

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
        wbool _loadLibs(errReport& rpt, bicontainable& tray);

    private:
        libHandles _handles;
    };
}
