#pragma once

#include "cast.hpp"

namespace wrd {

    class mgdCast: public cast {
        WRD_DECL_ME(mgdCast, cast)

    public:
        typedef wtype metaType;
        const wtype& getType() const override {
            return *_type;
        }
        WRD_INIT_META(me)

        explicit mgdCast(const wtype& type): _type(&type) {}

        const wtype* _type;
    };
}
