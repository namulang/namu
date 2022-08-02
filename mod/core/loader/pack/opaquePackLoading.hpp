#pragma once

#include "packLoading.hpp"

namespace namu {

    class errReport;
    class _wout opaquePackLoading : public packLoading {
        WRD(ADT(opaquePackLoading, packLoading))

    public:
        wbool verify(errReport& rpt, obj& pak) override;
    };
}
