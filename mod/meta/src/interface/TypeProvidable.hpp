#pragma once

namespace wrd {
    struct TypeProvidable {
        virtual const Type& getType() const = 0;
    };
}
