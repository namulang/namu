#pragma once

#include "core/loader/pack/packLoading.hpp"

namespace nm {

    class errReport;

    class _nout trustPackLoading: public packLoading {
        NM(ADT(trustPackLoading, packLoading))

    public:
        nbool verify(errReport& rpt, obj& pak) override;
    };
}
