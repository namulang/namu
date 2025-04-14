#pragma once

#include "../../../ast/slot.hpp"
#include "../../../ast/src/src.hpp"
#include "../../../loader/pack/trustPackLoading.hpp"

namespace nm {

    class _nout cppPackLoading: public trustPackLoading {
        NM(CLASS(cppPackLoading, trustPackLoading))
        typedef void (*entrypointFunc)(bicontainable*);

    public:
        tstr<srcs> parse(errReport& rpt, bicontainable& tray) override;
        const std::string& getName() const override;
        void rel() override;

    private:
        nbool _loadLibs(errReport& rpt, bicontainable& tray);

    private:
        dlibs _dlibs;
    };
}
