#pragma once

#include "As.hpp"

namespace wrd {

    class MgdAs: public As {
        WRD_DECL_THIS(MgdAs, As)

    public:
        typedef WType SuperType;
        const WType& getType() const override {
            return *_type;
        }
        WRD_INIT_META(This)

        explicit MgdAs(const WType& type): _type(&type) {}

        const WType* _type;
    };
}
