#pragma once

namespace wrd {
    struct TypeProvidable {
        virtual Type& getType() = 0;
    };
}
