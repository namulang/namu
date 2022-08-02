#pragma once

#include "packLoading.hpp"

namespace namu {

    class errReport;
    class _nout opaquePackLoading : public packLoading {
        WRD(ADT(opaquePackLoading, packLoading))

    public:
        nbool verify(errReport& rpt, obj& pak) override;
    };
}
