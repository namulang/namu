#pragma once

#include "../../../loader/pack/opaquePackLoading.hpp"
#include "../../../ast/src.hpp"
#include "../../../ast/slot.hpp"

namespace namu {

#ifdef NAMU_BUILD_PLATFORM_IS_WINDOWS
    typedef HMODULE libHandle;
#else
    typedef void* libHandle;
#endif
    typedef std::vector<libHandle> libHandles;

    class _nout cppPackLoading : public opaquePackLoading{
        WRD(CLASS(cppPackLoading, opaquePackLoading))
        typedef void (*entrypointFunc)(bicontainable*);

    public:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override;
        const std::string& getName() const override;
        void rel() override;

    private:
        nbool _loadLibs(errReport& rpt, bicontainable& tray);

    private:
        libHandles _handles;
    };

#include "../../../common/MSVCHack.hpp"

}
