#pragma once

#include "packLoading.hpp"

namespace wrd {

    class errReport;
    class _wout opaquePackLoading : public packLoading {
        WRD(ADT(opaquePackLoading, packLoading))

    public:
        wbool verify(errReport& rpt, pack& pak) override;
    };
}
