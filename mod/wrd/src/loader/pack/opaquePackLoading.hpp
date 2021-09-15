#pragma once

#include "packLoading.hpp"

namespace wrd {

    class opaquePackLoading : public packLoading {
        WRD(INTERFACE(opaquePackLoading, packLoading))

    public:
        wbool verify(const packChain& mergedPacks) override { return true; }
        wbool link(const packChain& mergedPacks) override { return true; }
    };
}
