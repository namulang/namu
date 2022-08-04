#pragma once

#include "packLoading.hpp"

namespace namu {

    class errReport;
    class _nout opaquePackLoading : public packLoading {
        NAMU(ADT(opaquePackLoading, packLoading))

    public:
        nbool verify(errReport& rpt, obj& pak) override;
    };
}
