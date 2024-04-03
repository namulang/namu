#pragma once

#include "../../type/ntype.hpp"
#include "../../common.hpp"

namespace namu {

    /// @remark arrayable has API treating index as its parameter.
    template <typename T, typename R = T&>
    class tarrayable {
        NAMU_ME(tarrayable)

    public:
        virtual ~tarrayable() {}

        // operator:
        virtual R operator[](nidx n) = 0;
        const R operator[](nidx n) const {
            return get(n);
        }

        // has:
        virtual nbool has(nidx n) const = 0;

        // get:
        virtual R get(nidx n) = 0;
        const R get(nidx n) const NAMU_UNCONST_FUNC(get(n))

        // set:
        virtual nbool set(nidx n, const T& new1) = 0;
        nbool set(nidx n, const T* new1) {
            return set(n, *new1);
        }

        // add:
        /// @return how many element has been added from rhs.
        virtual nbool add(nidx n, const T& new1) = 0;
        nbool add(nidx n, const T* new1) {
            return add(n, *new1);
        }

        // del:
        /// delete last element if exists.
        /// @return true if element got deleted successfully.
        virtual nbool del(nidx n) = 0;
    };
}
