#pragma once

#include "baseCtor.hpp"
#include "../params.hpp"

namespace nm {

    class visitor;

    class _nout defaultCopyCtor: public baseCtor {
        NM(CLASS(defaultCopyCtor, baseCtor), VISIT())

    public:
        defaultCopyCtor(const node& org);

    public:
        using super::run;
        str run(const args& a) override;

        using super::getParams;
        params& getParams() override;

    public:
        params _params;
    };
}
