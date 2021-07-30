#pragma once

#include "../common.hpp"
#include "interpretable.hpp"

namespace wrd {

    class interpreter : public interpretable {
        //TODO: WRD_CLASS(interpreter)

    public:
        wbool test(const wchar* msg) override;
    };

}
