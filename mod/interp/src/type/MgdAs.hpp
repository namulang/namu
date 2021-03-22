#pragma once

#include "Asable.hpp"

namespace wrd {

    class MgdAs: public TypeProvidable, public Asable {
        WRD_INTERFACE(MgdAs, Asable)

        MgdAs(const Type& type): _type(type) {}

        const Type& getType() const override {
            return *_type;
        }

        const Type* _type;
    };

    typedef std::vector<Asable*> Asables;
}
