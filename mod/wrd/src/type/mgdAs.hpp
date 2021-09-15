#pragma once

#include "cast.hpp"

namespace wrd {

    class mgdAs: public cast {
        WRD_DECL_ME(mgdAs, cast)

    public:
        typedef wtype metaType;
        const wtype& getType() const override {
            return *_type;
        }
        WRD_INIT_META(me)

        explicit mgdAs(const wtype& type): _type(&type) {}

        const wtype* _type;
    };
}
