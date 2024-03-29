#pragma once

#include "asable.hpp"

namespace namu {

    class ntype;
    template <typename T>
    struct tas : public asable, public typeProvidable {

    public:
        const type& getType() const override {
            return ttype<T>::get();
        }

        nbool is(const type& from, const type& to) const override {
            return getType() == to;
        }
    };
}
