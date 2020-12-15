#pragma once

namespace wrd { namespace meta {
    struct TypeProvidable {
        virtual const Type& getType() const = 0;
    };
}}
