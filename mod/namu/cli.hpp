#pragma once

#include "flag/flags.hpp"

namespace namu {

    struct cli {
        const flags& getFlags() const;

        nbool run(flagArgs& a);

        nint getRes() const;

    private:
        nint _finish(interpreter& ip);

    private:
        nint _res;
    };
}
