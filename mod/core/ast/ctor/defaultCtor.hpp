#pragma once

#include "baseCtor.hpp"
#include "../args.hpp"

namespace nm {

    class visitor;

    class _nout defaultCtor: public baseCtor {
        NM(ME(defaultCtor, baseCtor), CLONE(defaultCtor), VISIT())

    public:
        defaultCtor(const node& org);

    public:
        using super::run;
        str run(const args& a) override;
    };
}
