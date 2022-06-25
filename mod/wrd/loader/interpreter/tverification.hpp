#pragma once

#include "verification.hpp"

namespace wrd {

    template <typename T>
    class tverification : public verification {
        WRD(ME(tverification, verification),
            INIT_META(me))
        typedef wtype metaType;

    public:
        const wtype& getType() const override {
            return ttype<T>::get();
        }
    };
}
